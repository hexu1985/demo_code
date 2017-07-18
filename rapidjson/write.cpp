#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    rapidjson::Document document;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value root(rapidjson::kObjectType);
    root.AddMember("name", "哥伦布啊", allocator);
    root.AddMember("gold",1234,allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    root.Accept(writer);
    std::string reststring = buffer.GetString();
    std::cout << reststring << std::endl;

	return 0;
}
