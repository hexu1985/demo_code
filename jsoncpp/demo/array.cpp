#include <stdio.h>
#include <string>
#include <iostream>
#include "json_helper.h"

using namespace std;

int main()
{
    string info = R"({"id":"1111111","cards":[0,1,2,3,4,5,6,7,8,9],"jiaoDiZhu":""})";
    string err;

    Json::Value doc;
    Json_parse(info, &doc);

    const Json::Value &dataArray = doc["cards"];
    if (dataArray.isArray())
    {
        for (auto &object : dataArray)
        {
            printf("%d\n",object.asInt());
        }
    }

    return 0;
}

