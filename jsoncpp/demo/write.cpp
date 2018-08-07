#include <stdio.h>
#include <string>
#include <iostream>
#include <json/json.h>

using namespace std;

int main()
{
    Json::Value obj;
    obj["name"] = "哥伦布啊";
    obj["gold"] = 1234;

    std::cout << obj.toStyledString() << std::endl;

	return 0;
}
