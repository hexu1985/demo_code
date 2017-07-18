#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <boost/program_options.hpp>

#include "print_vm.h"

using namespace std;
using namespace boost::program_options;

int main(int argc, char* argv[])
{
    options_description opts("demo options");

    string filename;
    opts.add_options()

        ("help,h", "help message\n   a bit of long text")

        ("filename,f",
         value<string>(&filename)->default_value("test"), "to find a file")

        ("dir,D", value<vector<string> >()->multitoken(), "search dir")

        ("depth,d", value<int>()->implicit_value(5), "search depth")
        ;

    variables_map vm;
    store(parse_command_line(argc, argv, opts), vm);
    notify(vm);

    cout << "parse_command_line:\n";
    print_vm(opts, vm);
    cout << "\n=====================\n";

    stringstream ss;
    ss << "filename=a.cpp\ndir=/usr/bin\ndepth=10";
    store(parse_config_file(ss, opts), vm);

    ifstream ifs("config.ini");
    store(parse_config_file(ifs, opts, true), vm);

    const char *str = "config.ini";
    store(parse_config_file<char>(str, opts, true), vm);

    cout << "parse_config_file:\n";
    print_vm(opts, vm);

    return 0;
}
