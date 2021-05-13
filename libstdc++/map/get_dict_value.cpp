#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <cstdint>

template <typename T>
T get_dict_value(const std::map<std::string, std::string> &dict, const std::string &key, T default_val)
{
    auto iter = dict.find(key);
    if (iter == dict.end()) {
        return default_val;
    }

    T val;
    std::istringstream is(iter->second);
    is >> val;
    return val;
}

std::string get_dict_value(const std::map<std::string, std::string> &dict, const std::string &key, const std::string &default_val)
{
    auto iter = dict.find(key);
    if (iter == dict.end()) {
        return default_val;
    }

    return iter->second;
}

int main(int argc, char *argv[])
{
    std::map<std::string, std::string> dict = { 
        {"name", "xiao ming"}, 
        {"age", "30"}, 
        {"year", "1970"}, 
        {"month", "Jan"}, 
        {"day", "12"}, 
        {"male", "1"},
        {"id", "abc"},
    };

    std::string name = "default";
    name = get_dict_value(dict, "name", name);
    std::cout << "name: " << name << std::endl;

    std::string address = "default";
    address = get_dict_value(dict, "address", address);
    std::cout << "address: " << address << std::endl;

    uint64_t age = 0;
    age = get_dict_value(dict, "age", age);
    std::cout << "age: " << age << std::endl;

    int year = 0;
    year = get_dict_value(dict, "year", year);
    std::cout << "year: " << year << std::endl;

    uint32_t month = 0;
    month = get_dict_value(dict, "month", month);
    std::cout << "month: " << month << std::endl;

    bool male = false;
    male = get_dict_value(dict, "male", male);
    std::cout << "male: " << male << std::endl;


    return 0;
}
