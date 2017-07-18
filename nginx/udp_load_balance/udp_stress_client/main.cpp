#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <stdint.h>
#include "statistics.h"
#include "prog_opts_util.h"
#include "udp_connect.h"
#include "wrapsock.h"

using namespace std;
using namespace std::chrono;

struct Send_conf {
    int bytes_per_packet;
    int packets_per_request;
    int sleep_per_loop;
    std::atomic<uint32_t> total_send_packets;
    std::atomic<uint64_t> total_send_bytes;
};

struct Recv_conf {
    std::atomic<uint32_t> total_recv_packets;
    std::atomic<uint64_t> total_recv_bytes;
};

static void send_routine(vector<int> fd_set, Send_conf *send_conf);
static void recv_routine(vector<int> fd_set, Recv_conf *recv_conf);

int main(int argc, char *argv[])
{
    auto vm = Parse_command_line(argc, argv);
    cout << "program_options: \n";
    Print_variables_map(vm);
    cout << "\n\n" << endl;

    vector<int> fd_set;
    int client_number = vm["client_number"].as<int>();
    string server_host = vm["server_host"].as<string>();
    string server_port = vm["server_port"].as<string>();
    for (int i = 0; i < client_number; i++) {
	    int sockfd = Udp_connect(server_host.c_str(), server_port.c_str());
        fd_set.push_back(sockfd);
    } 

    Send_conf send_conf;
    send_conf.bytes_per_packet = vm["bytes_per_packet"].as<int>();
    send_conf.packets_per_request = vm["packets_per_request"].as<int>();
    send_conf.sleep_per_loop = vm["sleep_per_loop"].as<int>();
    send_conf.total_send_packets = 0;
    send_conf.total_send_bytes = 0;

    Recv_conf recv_conf;
    recv_conf.total_recv_packets = 0;
    recv_conf.total_recv_bytes = 0;

    std::thread send_thread(send_routine, fd_set, &send_conf);
    send_thread.detach();

    std::thread recv_thread(recv_routine, fd_set, &recv_conf);
    recv_thread.detach();

    int statistics_interval = vm["statistics_interval"].as<int>();
    Statistics st1, st2;
    while (true) {
        st1.total_send_packets = send_conf.total_send_packets;
        st1.total_send_bytes = send_conf.total_send_bytes;
        st1.total_recv_packets = recv_conf.total_recv_packets;
        st1.total_recv_bytes = recv_conf.total_recv_bytes;
        st1.time_point = steady_clock::now();
        this_thread::sleep_for(seconds(statistics_interval));
        st2.total_send_packets = send_conf.total_send_packets;
        st2.total_send_bytes = send_conf.total_send_bytes;
        st2.total_recv_packets = recv_conf.total_recv_packets;
        st2.total_recv_bytes = recv_conf.total_recv_bytes;
        st2.time_point = steady_clock::now();
        print_statistics(st1, st2);
    }

    return 0;
}

void send_routine(vector<int> fd_set, Send_conf *send_conf)
{
    auto bytes_per_packet = send_conf->bytes_per_packet;
    auto packets_per_request = send_conf->packets_per_request;
    auto sleep_per_loop = send_conf->sleep_per_loop;

    int nclient = fd_set.size();

    string buffer(bytes_per_packet, 'X');

    std::vector<std::string> data_set;
    data_set.resize(nclient);
    std::vector<const void *> buff_set;
    buff_set.resize(nclient);
    for (uint32_t i = 0; (int) i < nclient; i++) {
        memcpy(&buffer[1], &i, sizeof (i));
        data_set[i] = buffer;
        buff_set[i] = data_set[i].data();
    };

    for ( ; ; ) {
        for (int i = 0; i < nclient; i++) {
            for (int j = 0; j < packets_per_request; j++) {
                if (bytes_per_packet == send(fd_set[i], buff_set[i], bytes_per_packet, 0 /* MSG_DONTWAIT */)) {
                    send_conf->total_send_packets++;
                    send_conf->total_send_bytes += bytes_per_packet; 
                }
            }
        }

        this_thread::sleep_for(microseconds(sleep_per_loop));
    }
}

void recv_routine(vector<int> fd_set, Recv_conf *recv_conf)
{
    const int MAX_EVENTS = 5;
    const int BUF_SIZE = 8192;
    char      buff[BUF_SIZE];

    int    i, epfd, nready, sockfd, n;
    struct epoll_event  ev;
    struct epoll_event  evlist[MAX_EVENTS];

    epfd = Epoll_create(MAX_EVENTS);

    int nclient = fd_set.size();
    for (int i = 0; i < nclient; i++) {
        sockfd = fd_set[i];
        ev.data.fd = sockfd;
        ev.events = EPOLLIN; /* Only interested in input events */
        Epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
    }

	for ( ; ; ) {
		nready = Epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        for (i = 0; i < nready; i++) {
            if (evlist[i].events & EPOLLIN) {  /* net data in */
                sockfd = evlist[i].data.fd;
                if ((n = recv(sockfd, buff, BUF_SIZE, 0 /* MSG_DONTWAIT */)) > 0) {
                    recv_conf->total_recv_packets++;
                    recv_conf->total_recv_bytes += n;
                }
                continue;
            }
        }
    }
}
