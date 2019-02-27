#include <iostream>
#include <string>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main()
{
	string str = R"({"carriorName":"日本电信","deviceName":"iPhone5,2","osName":"android","osVersion":"8.1","appId":"com.mmcshadow.doudizhu","versionName":"1.0","versionCode":"1.0","deviceId":"11111111"})";

    auto json = json::parse(str);

//    cout << json["carriorName"] << endl;
    cout << json["carriorName"].get<string>() << endl;
    cout << setw(4) << json << endl;

	return 0;
}
