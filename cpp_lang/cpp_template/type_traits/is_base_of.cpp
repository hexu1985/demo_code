#include <iostream>
#include <type_traits>
#define SHOW(...) \
    std::cout << #__VA_ARGS__ << " : " \
              << std:: __VA_ARGS__ << '\n'
int main()
{
    class A {};
    class B : A {};
    class C : B {};
    class D {};
 
    std::cout << std::boolalpha;
    SHOW( is_base_of_v<A, A> );
    SHOW( is_base_of_v<A, B> );
    SHOW( is_base_of_v<A, C> );
    SHOW( is_base_of_v<A, D> );
    SHOW( is_base_of_v<B, A> );
    SHOW( is_base_of_v<int, int> );
}
