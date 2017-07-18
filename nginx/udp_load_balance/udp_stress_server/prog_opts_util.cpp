#include "prog_opts_util.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace boost::program_options;

variables_map Parse_command_line(int argc, char *argv[])
{
    options_description desc("udp_stree_client");

    string filename;
    desc.add_options()
        ("help,h", "produce help message")
        ("config_file,f", value<string>(&filename)->default_value(""), "config file")
        ("send_thread_number", value<int>()->default_value(1), "number of send thread")
        ("server_host", value<string>()->default_value("127.0.0.1"), "server host that client to connect")
        ("server_port", value<string>()->default_value("9999"), "server port that client to connect")
        ("bytes_per_packet", value<int>()->default_value(1000), "send packet size by bytes")
        ("rate_request_to_response", value<int>()->default_value(1), "when receive number of request to send a response")
        ("packets_per_response", value<int>()->default_value(1), "send packet number per response")
        ("statistics_interval", value<int>()->default_value(3), "statistics interval by seconds")
        ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (!filename.empty()) {
        ifstream ifs(filename);
        store(parse_config_file(ifs, desc, true), vm);
    }

    return vm;
}

void Print_variables_map(const boost::program_options::variables_map &vm)
{
    cout << "config_file: " << vm["config_file"].as<string>() << "\n";
    cout << "send_thread_number: " << vm["send_thread_number"].as<int>() << "\n";
    cout << "server_host: " << vm["server_host"].as<string>() << "\n";
    cout << "server_port: " << vm["server_port"].as<string>() << "\n";
    cout << "bytes_per_packet: " << vm["bytes_per_packet"].as<int>() << "\n";
    cout << "rate_request_to_response: " << vm["rate_request_to_response"].as<int>() << "\n";
    cout << "packets_per_response: " << vm["packets_per_response"].as<int>() << "\n";
    cout << "statistics_interval: " << vm["statistics_interval"].as<int>() << "\n";
}

