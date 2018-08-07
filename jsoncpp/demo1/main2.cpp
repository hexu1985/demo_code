#include <string>
#include <iostream>
#include <memory>
#include <json/json.h>

void readJson();
void writeJson();

int main(int argc, char** argv) {
	readJson();
	writeJson();
	return 0;
}

void readJson() {
	using namespace std;
	std::string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";

    Json::CharReaderBuilder reader_builder;
    std::auto_ptr<Json::CharReader> reader(reader_builder.newCharReader());
	Json::Value value;

    std::string errs;
	if (reader->parse(strValue.c_str(), strValue.c_str()+strValue.length(), &value, &errs))
	{
		std::string out = value["name"].asString();
		std::cout << out << std::endl;
		const Json::Value arrayObj = value["array"];
		for (unsigned int i = 0; i < arrayObj.size(); i++)
		{
			if (!arrayObj[i].isMember("cpp")) 
				continue;
			out = arrayObj[i]["cpp"].asString();
			std::cout << out;
			if (i != (arrayObj.size() - 1))
				std::cout << std::endl;
		}
	}
}

void writeJson() {
	using namespace std;

	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;

	item["cpp"] = "jsoncpp";
	item["java"] = "jsoninjava";
	item["php"] = "support";
	arrayObj.append(item);

	root["name"] = "json";
	root["array"] = arrayObj;

	root.toStyledString();
	std::string out = root.toStyledString();
	std::cout << out << std::endl;
}
