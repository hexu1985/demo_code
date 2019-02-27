#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using std::cout;
using std::endl;
using std::cin;

int main(int argc, const char * argv[]) {
    json temp;
    cin >> temp;
    cout << temp << endl;
    return 0;
}
/*
输入：
{
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
}
{"answer":{"everything":42},"happy":true,"list":[1,0,2],"name":"Niels","nothing":null,"object":{"currency":"USD","value":42.99},"pi":3.141}
Program ended with exit code: 0
*/

