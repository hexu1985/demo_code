#include <stdio.h>
#include <string>
#include <iostream>
#include "json11.hpp"

using namespace std;
using namespace json11;

int main()
{
    string info = R"({"id":"1111111","cards":[0,1,2,3,4,5,6,7,8,9],"jiaoDiZhu":""})";
    string err;

    auto doc = Json::parse(info, err);

    auto &dataArray = doc["cards"];

    if (!err.empty()) {
        cout << "parse json error: " << err << endl;
    }

    if (dataArray.is_array())
    {
        for (auto &object : dataArray.array_items())
        {
            printf("%d\n",object.int_value());
        }
    }

    return 0;
}

