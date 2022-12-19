
#include <iostream>
#include <string>
#include <tuple>

int main() {
    std::tuple<std::string, double> tp1;
    std::tuple<std::string, int> tp2;

    static_assert(std::is_same<std::tuple_element<1, decltype(tp1)>::type, double>::value, "type must be float point(like float, double, long double)");
    static_assert(std::is_same<std::tuple_element<1, decltype(tp2)>::type, double>::value, "type must be float point(like float, double, long double)");
}
