#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <stdint.h>
#include "config_parser.h"
#include "config_parser_util.h"

using namespace std;

int main(int argc, char *argv[])
{
    ConfigParser parser("test");
    parser.add_option("help,h")
          .add_string_option("config,f")
          .add_string_option("MT1DTESerial")
          .add_string_option("MT1DCESerial")
          .add_string_option("MT2DTESerial")
          .add_string_option("MT2DCESerial")
          .add_string_option("IPAddress")
          .add_int_option("Port");

    cout << "expect options: \n";
    parser.print_options_description(cout);
    cout << "\n";

    cout << "======================================================\n";
    cout << "==================parse_command_line==================\n";
    cout << "======================================================\n";
    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("help")) {
        cout << "options description: \n";
        parser.print_options_description(cout);
        cout << "\n\n";
    }

    cout << "parsed options: \n";
    print_parsed_options(cout, parser);
    cout << "\n";

    cout << "variables: \n";
    cout << "MT1DTESerial: " << parser.get_string_variables("MT1DTESerial", "/dev/null") << endl;
    cout << "MT1DCESerial: " << parser.get_string_variables("MT1DCESerial", "/dev/null") << endl;
    cout << "MT2DTESerial: " << parser.get_string_variables("MT2DTESerial", "/dev/null") << endl;
    cout << "MT2DCESerial: " << parser.get_string_variables("MT2DCESerial", "/dev/null") << endl;
    cout << "IPAddress: " << parser.get_string_variables("IPAddress", "0.0.0.0") << endl;
    cout << "Port: " << parser.get_int_variables("Port", 0) << endl;
    cout << "\n";

    cout << "======================================================\n";
    cout << "===================parse_environment==================\n";
    cout << "======================================================\n";
    std::map<std::string, std::string> name_map;
    name_map["IPADDRESS"] = "IPAddress";
    name_map["PORT"] = "Port";

    parser.parse_environment(name_map);

    cout << "parsed options: \n";
    print_parsed_options(cout, parser);
    cout << "\n";

    cout << "variables: \n";
    cout << "MT1DTESerial: " << parser.get_string_variables("MT1DTESerial", "/dev/null") << endl;
    cout << "MT1DCESerial: " << parser.get_string_variables("MT1DCESerial", "/dev/null") << endl;
    cout << "MT2DTESerial: " << parser.get_string_variables("MT2DTESerial", "/dev/null") << endl;
    cout << "MT2DCESerial: " << parser.get_string_variables("MT2DCESerial", "/dev/null") << endl;
    cout << "IPAddress: " << parser.get_string_variables("IPAddress", "0.0.0.0") << endl;
    cout << "Port: " << parser.get_int_variables("Port", 0) << endl;
    cout << "\n";

    cout << "======================================================\n";
    cout << "====================parse_file========================\n";
    cout << "======================================================\n";
    parser.parse_config_file(parser.get_string_variables("config", "IgsmrCaptureSet.ini"));

    cout << "parsed options: \n";
    print_parsed_options(cout, parser);
    cout << "\n";

    cout << "variables: \n";
    cout << "MT1DTESerial: " << parser.get_string_variables("MT1DTESerial", "/dev/null") << endl;
    cout << "MT1DCESerial: " << parser.get_string_variables("MT1DCESerial", "/dev/null") << endl;
    cout << "MT2DTESerial: " << parser.get_string_variables("MT2DTESerial", "/dev/null") << endl;
    cout << "MT2DCESerial: " << parser.get_string_variables("MT2DCESerial", "/dev/null") << endl;
    cout << "IPAddress: " << parser.get_string_variables("IPAddress", "0.0.0.0") << endl;
    cout << "Port: " << parser.get_int_variables("Port", 0) << endl;
    cout << "\n";

    return 0;
}

