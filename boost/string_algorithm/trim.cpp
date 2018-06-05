#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

using namespace boost::algorithm;
using namespace std;

int main()
{
    string str = "     abc     ...     ";
    cout << "before trim str = [" << str << "]" << endl;
    trim(str);
    cout << "after trim  str = [" << str << "]" << endl;

    string strOrigin = "12324342231436576abc0cba43455465767678878";
    str = strOrigin;
    cout << "before trim str = [" << str << "]" << endl;
    trim_if(str, is_any_of("1234567890"));
    cout << "after trim  str = [" << str << "]" << endl;
    string str2 = trim_copy_if(strOrigin, is_any_of("1234567890"));
    cout << "after trim  str2 = [" << str2 << "]" << endl;
    string str3 = trim_left_copy_if(strOrigin, is_any_of("1234567890"));
    cout << "after trim  str3 = [" << str3 << "]" << endl;
    string str4 = trim_right_copy_if(strOrigin, is_any_of("1234567890"));
    cout << "after trim  str4 = [" << str4 << "]" << endl;
    trim_left_if(strOrigin, is_any_of("1234567890"));
    cout << "after tim_left , strOrigin = [" << strOrigin << "]" << endl;
    trim_right_if(strOrigin, is_any_of("1234567890"));
    cout << "after tim_right, strOrigin = [" << strOrigin << "]" << endl;
    return 0;
}
