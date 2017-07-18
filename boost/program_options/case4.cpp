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

    positional_options_description pod;
    pod.add("filename", 1).add("dir", 2).add("depth", -1);
    auto pr =
        command_line_parser(argc, argv).
            options(opts).
                positional(pod).
                    run();
                    store(pr, vm );

    notify(vm);
    print_vm(opts, vm);

    return 0;
}
