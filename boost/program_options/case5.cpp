#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <boost/program_options.hpp>

#include "print_vm.h"

using namespace std;
using namespace boost::program_options;

string name_mapper(const string& env_name)
{
    static map<string, string> nm =
        {{"HOME", "home"},{"USER", "uname"}};

    return nm[env_name];
}

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
        ("home", value<string>(), "home dir")
        ("uname", value<string>(), "user's name")

        ;

    variables_map vm;

    store(parse_environment(opts, name_mapper),vm);
    cout << vm["home"].as<string> ()<< endl;
    cout << vm["uname"].as<string> ()<< endl;

    notify(vm);
    print_vm(opts, vm);

    return 0;
}
