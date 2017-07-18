#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

using namespace std;

void map2json(std::string &json_str, const std::map<std::string, std::string> &kv_map)
{
    json_str = "";

    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    rapidjson::Value key;
    rapidjson::Value value;
    for (const auto &item: kv_map) {
        key.SetString(item.first.c_str(), item.first.length(), allocator);
        value.SetString(item.second.c_str(), item.second.length(), allocator);
        document.AddMember(key, value, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    json_str = buffer.GetString();
}

int main()
{
    std::map<std::string, std::string> kv_map = { {"hello", "world"}, {"c++", "java"},};
    std::string json_str;
    map2json(json_str, kv_map);

    std::cout << "json_str: " << json_str << std::endl;

	return 0;
}
