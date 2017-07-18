#include "statistics.h"
#include <iostream>

using namespace std;
using namespace std::chrono;

void print_statistics(const Statistics &begin, const Statistics &end)
{
    system_clock::time_point now = system_clock::now();
    std::time_t tt = system_clock::to_time_t(now);
    cout << "time: " << ctime(&tt);

    duration<double> time_span = duration_cast<duration<double>>(end.time_point - begin.time_point);
    cout << "time_span: " << time_span.count() << " seconds\n";

    cout << "total_send_packets: " << end.total_send_packets << '\n';  
    cout << "total_send_bytes: " << end.total_send_bytes << '\n';  
    cout << "total_recv_packets: " << end.total_recv_packets << '\n';  
    cout << "total_recv_bytes: " << end.total_recv_bytes << '\n';  

    int send_packets = end.total_send_packets - begin.total_send_packets;
    cout << "send_packets: " << send_packets << '\n';  

    int send_bytes = end.total_send_bytes - begin.total_send_bytes;
    cout << "send_bytes: " << send_bytes << '\n';  

    int recv_packets = end.total_recv_packets - begin.total_recv_packets;
    cout << "recv_packets: " << recv_packets << '\n';  

    int recv_bytes = end.total_recv_bytes - begin.total_recv_bytes;
    cout << "recv_bytes: " << recv_bytes << '\n';  

    double send_pps = send_packets / time_span.count();
    double send_bps = send_bytes / time_span.count() / 1000000 * 8;
    cout << "send pps: " << send_pps << " packet/second\n";
    cout << "send bps: " << send_bps << " MBit/s\n";

    double recv_pps = recv_packets / time_span.count();
    double recv_bps = recv_bytes / time_span.count() / 1000000 * 8;
    cout << "recv pps: " << recv_pps << " packet/second\n";
    cout << "recv bps: " << recv_bps << " MBit/s\n";
    cout << "\n\n" << endl;
}
