#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

using namespace std;

std::string to_string(const rapidjson::Value &value)
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);
    return buffer.GetString();
}

void json2map(std::map<std::string, std::string> &kv_map, const std::string &json_str)
{
	kv_map.clear();

	rapidjson::Document document;
	document.Parse(json_str.c_str());
	for (rapidjson::Value::ConstMemberIterator iter = document.MemberBegin(); iter != document.MemberEnd(); ++iter)
	{
        if (iter->value.IsString())
            kv_map[iter->name.GetString()] = iter->value.GetString();
        else 
            kv_map[iter->name.GetString()] = to_string(iter->value);
	}
}

std::string to_string(const std::map<std::string, std::string> &kv_map)
{
    std::string str;
    str += "{";
    for (const auto &item: kv_map) {
        str += "{" + item.first + "," + item.second + "}, ";
    }
    str += "}";
    return str;
}

int main()
{
    std::string json_str = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4], \"c++\": \"java\" , \"object\": { \"name\": \"hexu\" } } ";
    std::map<std::string, std::string> kv_map;

	json2map(kv_map, json_str);

    std::cout << "json_str: " << json_str << std::endl;
	std::cout << "map: " << to_string(kv_map) << std::endl;

	return 0;
}
