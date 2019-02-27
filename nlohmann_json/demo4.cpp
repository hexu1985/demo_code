#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using std::cout;
using std::endl;
using std::cin;

int main(int argc, const char * argv[]) {

	{
		json array = {
			"yan",12,"ze",13
		};
		cout << array[0] << endl;
	}

	{
		json array = {
			{"yan",12},
			"ze",13
		};
		cout << array[0][0] << endl;
	}

	{
		json array = {
			{{"yan",12}},
			"ze",13
		};
		cout << array[0]["yan"] << endl;
	}

	{
		json array = {
			{"yan",12},
			{"ze",13}
		};
		cout << array["yan"] << endl;
	}

	{
		json array = {
			{
				{"yan",12}
			},
			{
				{"ze",13}
			}
		};
		cout << array[0]["yan"] << endl;
	}

	return 0;
}

