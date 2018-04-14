#include "config_parser.h"
#include <iostream>

void print_parsed_options(std::ostream& os, const ConfigParser &parser)
{
    std::vector<std::string> parsed_options = parser.get_parsed_options();
    for (size_t i = 0; i < parsed_options.size(); i++) {
        os << parsed_options[i] << '\n';
    }
}

