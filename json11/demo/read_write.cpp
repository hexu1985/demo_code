#include <iostream>
#include <string>
#include "json11.hpp"

using namespace std;
using namespace json11;

int main()
{
	//read json
	string updateInfo = "{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\"}]}";
    string err;

	Json doc;
    doc = Json::parse(updateInfo, err);

    if (!err.empty()) {
        cout << "parse json error: " << err << endl;
    }

	auto &dataArray = doc["UpdateInfo"];

	if (dataArray.is_array())
	{
        for (auto &object : dataArray.array_items())
        {
			string url = object["url"].string_value();
			string platform = object["platform"].string_value();
        }
	}

	//write json
	Json document;

    Json::array array;

	for (int i = 0; i < 10; i++)
	{
        Json object = Json::object({
                {"id", 1},
                {"name", "test"},
                {"version", 1.01},
                {"vip", true}
                });

        object = Json(i);
		array.push_back(object);
	}

    document = Json::object({
            {"title", "PLAYER INFO"},
            {"players", array}
            });

	printf("out: %s\n", document.dump().c_str());

    return 0;
}
