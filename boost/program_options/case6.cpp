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
    options_description opts1("group 1");
    opts1.add_options()
        ("help,h", "help message");

    options_description opts2("group 2(hide)");
    opts2.add_options()
        ("filename,f", value<string>(), "to find a file");

    options_description opts3("group 3");
    opts3.add_options()
        ("dir,D", value<vector<string> >()->composing(), "search dir")
        ("depth,d", value<int>(), "search depth");

    options_description opts_all;
    opts_all.add(opts1).add(opts2).add(opts3);

    options_description opts_cfgfile;
    opts_cfgfile.add(opts2).add(opts3);

    options_description opts_showhelp("demo options");
    opts_showhelp.add(opts1).add(opts3);

    variables_map vm;

    store(parse_command_line(argc, argv, opts_all), vm);
    store(parse_config_file<char>("config.ini", opts_cfgfile, true), vm);

    if (vm.count("help") || vm.empty())
    {
        cout << opts_showhelp << endl;
        return 1;
    }

    notify(vm);
    print_vm(opts_all, vm);

    return 0;
}
