#include <iostream>
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;
int main() {
    fs::path p1; // 空路径
    p1 += "var"; // 不插入分隔符
    std::cout << "\"\" + \"var\" == " << p1 << '\n';
    p1 += "lib"; // does not insert a separator
    std::cout << "\"\" + \"var\" + \"lib\" == " << p1 << '\n';
}
