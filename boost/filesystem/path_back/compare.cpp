#include <iostream>
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;

void demo(int rc, fs::path p1, fs::path p2) {
    if(rc < 0) std::cout << p1 << " < " << p2 << '\n';
    else if(rc > 0) std::cout << p1 << " > "  << p2 << '\n';
    else if(rc == 0) std::cout << p1 << "==" << p2 << '\n';
}

int main() {
    fs::path p1 = "/a/b/"; // 对于字典迭代如同 "a/b/."
    fs::path p2 = "/a/b/#";
    demo(p1.compare(p2), p1, p2);
    demo(p1.compare("a/b/_"), p1, "a/b/_");
}
