#include <boost/optional.hpp>
#if __cplusplus >= 201103L
#include <initializer_list>
#endif
#include <iostream>
#include <string>

int main()
{
    boost::optional<int> o1, // 空
                       o2 = 1, // 从右值初始化
                       o3 = o2; // 复制构造函数
 
    // 调用 std::string( initializer_list<CharT> ) 构造函数
#if __cplusplus >= 201103L
    boost::optional<std::string> o4(boost::in_place_init, std::initializer_list<char>({'a', 'b', 'c'}));
#else
    boost::optional<std::string> o4(boost::in_place_init, "abc");
#endif
 
    // 调用 std::string( size_type count, CharT ch ) 构造函数
    boost::optional<std::string> o5(boost::in_place_init, 3, 'A');
 
    // 从 std::string 移动构造，用推导指引拾取类型
 
#if __cplusplus >= 201103L
    boost::optional<std::string> o6(std::string{"deduction"});
#else
    boost::optional<std::string> o6(std::string("deduction"));
#endif
 
    std::cout << *o2 << ' ' << *o3 << ' ' << *o4 << ' ' << *o5  << ' ' << *o6 << '\n';
}
