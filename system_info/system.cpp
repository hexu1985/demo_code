#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {

  cout << "begin system" << endl;

  system("firefox \"https://www.baidu.com/\" &");
//  system("sleep 3 &");

  cout << "after system" << endl;

  cin.get();

  return 0;
}
