#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;

int main()
{
    fs::path p = "C:/users/abcdef/AppData/Local";
    p = p / "Temp"; // 移动赋值
    const wchar_t* wstr = L"D:/猫.txt";
    p = wstr; // 从源赋值
}
