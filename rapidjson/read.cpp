#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
	char json[] = "{\"carriorName\":\"日本电信\",\"deviceName\":\"iPhone5,2\",\"osName\":\"android\",\"osVersion\":\"8.1\",\"appId\":\"com.mmcshadow.doudizhu\",\"versionName\":\"1.0\",\"versionCode\":\"1.0\",\"deviceId\":\"11111111\"}";
	rapidjson::Document d;
	d.Parse<0>(json);
	printf("%s\n", d["carriorName"].GetString());
	printf("%s\n", json);

	return 0;
}
