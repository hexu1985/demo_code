#include <stdio.h>
#include <string>
#include "json_helper.h"

using namespace std;

int main()
{
	//read json
	string updateInfo = "{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\"}]}";

    Json::Value doc;
    Json_parse(updateInfo, &doc); 

	const Json::Value &dataArray = doc["UpdateInfo"];

	if (dataArray.isArray())
	{
		for (int i = 0; i < dataArray.size(); i++)
		{
			const Json::Value& object = dataArray[i];

			string url = object["url"].asString();
			string platform = object["platform"].asString();
		}
	}

	//write json
    Json::Value document;

	Json::Value array;

	for (int i = 0; i < 10; i++)
	{
		Json::Value object;
        object["id"] = 1;
        object["name"] = "test";
        object["version"] = 1.01;
        object["vip"] = true;

        object = Json::Value(i);
		array.append(object);
	}

    document["title"] = "PLAYER INFO";
    document["players"] = array;

    std::string out = document.toStyledString();
	printf("out: %s\n", out.c_str());

    return 0;
}
