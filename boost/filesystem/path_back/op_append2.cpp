#include <iostream>
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;
int main() {
    fs::path p1 = "C:";
    p1 /= "Users"; // 不插入分隔符
    std::cout << "\"C:\" / \"Users\" == " << p1 << '\n';
    p1 /= "batman"; // 插入 fs::path::preferred_separator ，在 Windows 上为 '\'
    std::cout << "\"C:\" / \"Users\" / \"batman\" == " << p1 << '\n';
}
