#include <string>
#include <iostream>
#include <exception>
#include <boost/program_options.hpp>

using namespace std;
using namespace boost::program_options;

int main(int argc, char *argv[])
{
    options_description opts("demo options");

    opts.add_options()
        ("help", "just a help info")
        ("filename,f", value<string>(), "to find a file")
        ;

    variables_map vm;
    try {
        store(parse_command_line(argc, argv, opts), vm);
    } catch (const exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << opts << std::endl;
        return 1;
    }

    if (vm.count("help")) {
        cout << opts << endl;
        return 0;
    }

    if (vm.count("filename")) {
        cout << "find " << vm["filename"].as<string>() << endl;
    }

    if (vm.empty()) {
        cout << "no options" << endl;
    }

    return 0;
}
