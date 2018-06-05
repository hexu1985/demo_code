#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace boost::algorithm;
using namespace std;

int main()
{
    string str("miss,you.just.call_to,say,I~love~you");
    vector<string> strVec;
    split(strVec, str, is_any_of(",."));
    vector<string>::iterator it = strVec.begin();
    for (; it!=strVec.end(); it++){
        cout << *it << endl;
    }
    return 0;
}
