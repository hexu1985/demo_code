#include <boost/optional.hpp>
#include <iostream>
#include <string>
 
int main()
{
#if __cplusplus >= 201402L 
    using namespace std::string_literals;
#endif
    boost::optional<int> opt1 = 1;
    std::cout<< "opt1: "  << *opt1 << '\n';
 
    *opt1 = 2;
    std::cout<< "opt1: "  << *opt1 << '\n';
 
#if __cplusplus >= 201402L 
    boost::optional<std::string> opt2 = "abc"s;
#else
    boost::optional<std::string> opt2 = std::string("abc");
#endif
    std::cout<< "opt2: " << *opt2 << " size: " << opt2->size() << '\n';
 
    // 你能通过在到 optional 的右值上调用 operator* “取”其所含值
#if __cplusplus >= 201103L 
    auto taken = *std::move(opt2);
    std::cout << "taken: " << taken << " opt2: " << *opt2 << "size: " << opt2->size()  << '\n';
#endif
}
