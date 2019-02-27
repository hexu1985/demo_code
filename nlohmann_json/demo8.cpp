#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using std::cout;
using std::endl;
using std::cin;

int main(int argc, const char * argv[]) {
	//明确解析
	auto j3 = json::parse(" { \"happy\": true, \"pi\":3.141 } ");
	cout << j3 << endl;
	cout << j3["happy"] << endl;
	cout << j3["pi"] << endl;
	bool is_happy = j3["happy"];
	double pi = j3["pi"];
	cout << is_happy << endl;
	cout << pi << endl;
	return 0;
}

