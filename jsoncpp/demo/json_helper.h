#ifndef json_helper_h
#define json_helper_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <json/json.h>

inline void Json_parse(const std::string& str, Json::Value *root)
{
    Json::CharReaderBuilder reader_builder;
    std::unique_ptr<Json::CharReader> reader(reader_builder.newCharReader());

    std::string errs;
	if (!reader->parse(str.c_str(), str.c_str()+str.length(), root, &errs)) {
        std::cerr << "parser json error: " << errs << ". \n"; 
        exit(1);
    }
}

inline void Json_parse(std::istream &in, Json::Value *root)
{
    Json::CharReaderBuilder reader_builder;
    std::string errs;
    if (!Json::parseFromStream(reader_builder, in, root, &errs)) {
        std::cerr << "parser json error: " << errs << ". \n"; 
        exit(1);
    }
}

#endif

