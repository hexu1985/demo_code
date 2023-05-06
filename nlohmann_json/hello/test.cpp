#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

int main() {
	json j;			// 创建 json 对象
	ifstream jfile("test.json");
	jfile >> j;		// 以文件流形式读取 json 文件
	float pi = j.at("pi");
    cout << "pi: " << pi << endl;
	bool happy = j.at("happy");
    cout << "happy: " << happy << endl;
	return 0;
}
