#include <boost/optional.hpp>
#include <iostream>

int main()
{
    boost::optional<int> opt = {};
 
    try {
        int n = opt.value();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
    }
}
