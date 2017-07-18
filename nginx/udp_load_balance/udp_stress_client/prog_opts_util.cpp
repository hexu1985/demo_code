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
        ("client_number", value<int>()->default_value(1), "number of client")
        ("server_host", value<string>()->default_value("127.0.0.1"), "server host that client to connect")
        ("server_port", value<string>()->default_value("9999"), "server port that client to connect")
        ("bytes_per_packet", value<int>()->default_value(1000), "send packet size by bytes")
        ("packets_per_request", value<int>()->default_value(1), "send packet number per request")
        ("sleep_per_loop", value<int>()->default_value(100), "sleep us per send loop")
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
    cout << "client_number: " << vm["client_number"].as<int>() << "\n";
    cout << "server_host: " << vm["server_host"].as<string>() << "\n";
    cout << "server_port: " << vm["server_port"].as<string>() << "\n";
    cout << "bytes_per_packet: " << vm["bytes_per_packet"].as<int>() << "\n";
    cout << "packets_per_request: " << vm["packets_per_request"].as<int>() << "\n";
    cout << "sleep_per_loop: " << vm["sleep_per_loop"].as<int>() << "\n";
    cout << "statistics_interval: " << vm["statistics_interval"].as<int>() << "\n";
}

