#include <iostream>
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    fs::path p1 = "/usr/lib/sendmail.cf"; // 可移植格式
    fs::path p2 = "C:\\users\\abcdef\\AppData\\Local\\Temp\\"; // 原生格式
    fs::path p3 = L"D:/猫.txt"; // 宽字符串

    std::cout << "p1 = " << p1 << '\n'
            << "p2 = " << p2 << '\n'
            << "p3 = " << p3 << '\n';
}
