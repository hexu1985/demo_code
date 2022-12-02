// set_difference example
#include <iostream>     // std::cout
#include <set>          // std::set

#include <algorithm>    // std::set_difference, std::sort
#include <vector>       // std::vector

template <typename T>
std::set<T> set_difference(const std::set<T>& a, const std::set<T>& b) {    // return a-b 
    std::set<T> c = a;
    for (const auto& elem : b) {
        c.erase(elem);
    }
    return c;
}

template <typename T>
std::set<T> operator-(const std::set<T>& a, const std::set<T>& b) {
    return set_difference(a, b);
}

int main () {
    std::set<int> first{5,10,15,20,25};
    std::set<int> second{50,40,30,20,10};

    auto c = first - second;
    std::cout << "The difference has " << (c.size()) << " elements:\n";
    for (auto it=c.begin(); it!=c.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}
