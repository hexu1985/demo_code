#include <iostream>
#include <string>
#include "json11.hpp"

using namespace std;
using namespace json11;

int main()
{
	string str = R"({"carriorName":"日本电信","deviceName":"iPhone5,2","osName":"android","osVersion":"8.1","appId":"com.mmcshadow.doudizhu","versionName":"1.0","versionCode":"1.0","deviceId":"11111111"})";
    string err;

    auto json = Json::parse(str, err);

    if (!err.empty()) {
        cout << "parse json error: " << err << endl;
    }

    cout << json["carriorName"].string_value() << endl;
    cout << str << endl;

	return 0;
}
