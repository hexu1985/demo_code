#include <iostream>
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;

int main()
{
    // 其中 "//host" 是根名
    std::cout << '\n' << fs::path("//host")  / "foo"; // 结果是      "//host/foo" (附加分隔符)
    std::cout << '\n' << fs::path("//host/") / "foo"; // 结果亦为    "//host/foo" (附加，无分隔符)

    // POSIX 上，
    std::cout << '\n' << fs::path("foo") / "";      // 结果是 "foo/" (附加)
    std::cout << '\n' << fs::path("foo") / "/bar"; // 结果是 "/bar" (替换)

    // Windows 上，
    std::cout << '\n' << fs::path("foo") / "C:/bar";  // 结果是 "C:/bar"    (替换)
    std::cout << '\n' << fs::path("foo") / "C:";      // 结果是 "C:"        (替换)
    std::cout << '\n' << fs::path("C:") / "";         // 结果是 "C:"        (附加，不带分隔符)
    std::cout << '\n' << fs::path("C:foo") / "/bar";  // 生成   "C:/bar"    (移除相对路径后附加)
    std::cout << '\n' << fs::path("C:foo") / "C:bar"; // 生成   "C:foo/bar" (附加，忽略 p 的根名)
    std::cout << std::endl;

    return 0;
}
