#include "config_parser.h"
#include <fstream>

ConfigParser::ConfigParser(const std::string &caption): desc_(caption)
{
}

ConfigParser &ConfigParser::add_option(const std::string &name, 
        const std::string &description) 
{
    desc_.add_options()(name.c_str(), description.c_str());
    return *this;
}

ConfigParser &ConfigParser::add_int_option(const std::string &name, 
        const std::string &description)
{
    desc_.add_options()(name.c_str(), 
            boost::program_options::value<int>(), description.c_str());
    return *this;
}

ConfigParser &ConfigParser::add_string_option(const std::string &name, 
        const std::string &description)
{
    desc_.add_options()(name.c_str(), 
            boost::program_options::value<std::string>(), description.c_str());
    return *this;
}

void ConfigParser::parse_command_line(int argc, const char* const argv[])
{
    boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, desc_), vm_);
}

void ConfigParser::parse_config_file(const std::string &filename)
{
    std::ifstream ifs(filename.c_str());
    boost::program_options::store(
            boost::program_options::parse_config_file(ifs, desc_, true), vm_);
}

bool ConfigParser::has_variables(const std::string &option)
{
    return vm_.count(option);
}

int ConfigParser::get_int_variables(const std::string &option)
{
    return vm_[option].as<int>();
}

int ConfigParser::get_int_variables(const std::string &option, int default_value)
{
    if (!has_variables(option))
        return default_value;
    return get_int_variables(option);
}

std::string ConfigParser::get_string_variables(const std::string &option)
{
    return vm_[option].as<std::string>();
}

std::string ConfigParser::get_string_variables(const std::string &option, 
        const std::string &default_value)
{
    if (!has_variables(option))
        return default_value;
    return get_string_variables(option);
}

void ConfigParser::print_options_description(std::ostream& os) const
{
    desc_.print(os);
}

std::vector<std::string> ConfigParser::get_parsed_options() const
{
    boost::program_options::variables_map::const_iterator iter, end;
    std::vector<std::string> parsed_options;
    for (iter = vm_.begin(), end = vm_.end() ; iter != end; iter++) {
        parsed_options.push_back(iter->first);
    }
    return parsed_options;
}

