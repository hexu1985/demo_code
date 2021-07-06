#include<iostream>
#include<utility>
#include<type_traits>

template<typename T>
struct has_member_foo
{
private:
    template<typename U>
        static auto Check(int) -> decltype( std::declval<U>().foo(), std::true_type() );
    template<typename U>
        static std::false_type Check(...);
public:
    enum { value = std::is_same<decltype(Check<T>(0)),std::true_type>::value  };
};

struct myStruct
{
    void foo() { std::cout << "hello" << std::endl;  }
};

struct another
{
    void test() { std::cout << "test" << std::endl;  }
};

int main()
{
    if( has_member_foo<myStruct>::value )
    	std::cout << "myStruct has foo funciton"  << std::endl;
    else
        std::cout << "myStruct does't have foo funciton"  << std::endl;

    if( has_member_foo<another>::value )
    	std::cout << "another has foo function"  << std::endl;
    else
	std::cout << "another does't have foo function"  << std::endl;
    return 0;
}
