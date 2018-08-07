#include <iostream>
#include <string>
#include "json_helper.h"

using namespace std;

int main()
{
	string str = R"({"carriorName":"日本电信","deviceName":"iPhone5,2","osName":"android","osVersion":"8.1","appId":"com.mmcshadow.doudizhu","versionName":"1.0","versionCode":"1.0","deviceId":"11111111"})";
    string err;

    Json::Value json; 
    Json_parse(str, &json);

    cout << json["carriorName"].asString() << endl;
    cout << str << endl;

	return 0;
}
