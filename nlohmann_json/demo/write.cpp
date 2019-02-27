#include <stdio.h>
#include <string>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main()
{
    const json obj = {
            {"name", "哥伦布啊"},
            {"gold", 1234}
            };
    std::cout << obj.dump() << std::endl;

	return 0;
}
