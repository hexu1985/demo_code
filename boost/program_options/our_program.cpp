#include <boost/program_options.hpp>

// 'reading_file' exception class is declared in errors.hpp
#include <boost/program_options/errors.hpp>
#include <iostream>
#include <exception>

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
	opt::options_description desc("All options");

	// 'a' and 'o' are short option names for apples and
	// oranges 'name' option is not marked with
	// 'required()', so user may not support it
	desc.add_options()
		("apples,a", opt::value<int>()->default_value(10), "apples that you have")
		("oranges,o", opt::value<int>(), "oranges that you have")
		("name", opt::value<std::string>(), "your name")
		("help", "produce help message")
		;
	opt::variables_map vm;
	// Parsing command line options and storing values to 'vm'

    try {
        opt::store(opt::parse_command_line(argc, argv, desc), vm);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }

	// We can also parse environment variables using
	// 'parse_environment' method
	opt::notify(vm);
	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	// Adding missing options from "aples_oranges.cfg"
	// config file.
	// You can also provide an istreamable object as a
	// first parameter for 'parse_config_file'
	// 'char' template parameter will be passed to
	// underlying std::basic_istream object
	try {
		opt::store(
				opt::parse_config_file<char>("apples_oranges.cfg", desc),
				vm
				);
	} catch (const opt::reading_file& e) {
		std::cout
			<< "Failed to open file 'apples_oranges.cfg': "
			<< e.what();
	}
	opt::notify(vm);
	if (vm.count("name")) {
		std::cout << "Hi," << vm["name"].as<std::string>() << "!\n";
	}
	std::cout << "Fruits count: "
		<< (vm.count("apples") ? vm["apples"].as<int>() : 0) + (vm.count("oranges") ? vm["oranges"].as<int>() : 0)
		<< std::endl;
	return 0;
}
