#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	//read json
	string updateInfo = "{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\"}]}";

	rapidjson::Document doc;
	doc.Parse<0>(updateInfo.c_str());

	rapidjson::Value &dataArray = doc["UpdateInfo"];

	if (dataArray.IsArray())
	{
		for (int i = 0; i < dataArray.Size(); i++)
		{
			const rapidjson::Value& object = dataArray[i];

			string url = object["url"].GetString();
			string platform = object["platform"].GetString();
		}
	}

	//write json
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value array(rapidjson::kArrayType);

	for (int i = 0; i < 10; i++)
	{
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("id", 1, allocator);
		object.AddMember("name", "test", allocator);
		object.AddMember("version", 1.01, allocator);
		object.AddMember("vip", true, allocator);

		object.SetInt(i);
		array.PushBack(object, allocator);
	}

	document.AddMember("title", "PLAYER INFO", allocator);
	document.AddMember("players", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	auto out = buffer.GetString();
	printf("out: %s\n", out);

    return 0;
}
