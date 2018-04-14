#ifndef __config_parser_h
#define __config_parser_h

#include <iosfwd>
#include <string>
#include <vector>
#include <map>
#include "boost/program_options.hpp"

class ConfigParser {
private:
    boost::program_options::options_description desc_;
    boost::program_options::variables_map vm_;

public:
    ConfigParser(const std::string &caption); 

    ConfigParser &add_option(const std::string &name, const std::string &description = "");
    ConfigParser &add_int_option(const std::string &name, const std::string &description = "");
    ConfigParser &add_string_option(const std::string &name, const std::string &description = "");

    void parse_command_line(int argc, const char* const argv[]);
    void parse_environment(const std::map<std::string, std::string> &name_map);
    void parse_config_file(const std::string &filename);

    bool has_parsed_option(const std::string &option);

    int get_int_variables(const std::string &option);
    int get_int_variables(const std::string &option, int default_value);

    std::string get_string_variables(const std::string &option);
    std::string get_string_variables(const std::string &option, const std::string &default_value);

    void print_options_description(std::ostream& os) const;
    std::vector<std::string> get_parsed_options() const;

protected:
    const boost::program_options::options_description &get_options_description() const
    {
        return desc_;
    }

    const boost::program_options::variables_map &get_variables_map() const
    {
        return vm_;
    }

    boost::program_options::options_description &get_options_description()
    {
        return desc_;
    }

    boost::program_options::variables_map &get_variables_map()
    {
        return vm_;
    }
};

#endif

