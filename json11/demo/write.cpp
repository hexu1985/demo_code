#include <stdio.h>
#include <string>
#include <iostream>
#include "json11.hpp"

using namespace std;
using namespace json11;

int main()
{
    const Json obj = Json::object({
            {"name", "哥伦布啊"},
            {"gold", 1234}
            });
    std::cout << obj.dump() << std::endl;

	return 0;
}
