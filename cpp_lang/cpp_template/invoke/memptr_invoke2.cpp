#include <iostream>
#include <type_traits>

// a class with data members:
struct MyValue {
  int value;
  int fifth() {return value/5;}
};

template <typename MT1, typename B, typename T>
void memptr_inovke(MT1 B::*pmf, T&& t, const std::string& desc)
{
    std::cout << "call " << desc; 
    if constexpr (std::is_function_v<MT1>) {
        std::cout << " is member function";
        if constexpr (std::is_base_of_v<B, std::decay_t<T>>) {
            std::cout << " with object: " << (t.*pmf)();
        } else {
            std::cout << " with ptr: " << (t->*pmf)();
        }
    } else {
        static_assert(std::is_object_v<MT1>);
        std::cout << " is member variable";
        if constexpr (std::is_base_of_v<B, std::decay_t<T>>) {
            std::cout << " with object: " << t.*pmf;
        } else {
            std::cout << " with ptr: " << t->*pmf;
        }
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    MyValue sixty {60};

    memptr_inovke(&MyValue::value, sixty, "memptr_inovke(&MyValue::value, sixty)");
    memptr_inovke(&MyValue::fifth, sixty, "memptr_inovke(&MyValue::fifth, sixty)");
    memptr_inovke(&MyValue::value, &sixty, "memptr_inovke(&MyValue::value, &sixty)");
    memptr_inovke(&MyValue::fifth, &sixty, "memptr_inovke(&MyValue::fifth, &sixty)");
    return 0;
}

