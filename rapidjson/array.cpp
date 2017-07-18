#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
    string info = "{\"id\":\"1111111\",\"cards\":[0,1,2,3,4,5,6,7,8,9],\"jiaoDiZhu\":\"\"}";

    rapidjson::Document doc;
    doc.Parse<0>(info.c_str());

    rapidjson::Value &dataArray = doc["cards"];

    if (dataArray.IsArray())
    {
        for (rapidjson::SizeType i = 0; i < dataArray.Size(); i++)
        {
            const rapidjson::Value& object = dataArray[i];

            printf("%d\n",object.GetInt());
        }
    }

    return 0;
}

