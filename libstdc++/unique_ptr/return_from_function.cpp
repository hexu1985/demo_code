#include <memory>
#include <iostream>

std::unique_ptr<int> get_int_ptr(int n) {
    auto ptr = std::unique_ptr<int>(new int{n});
    std::cout << "get_int_ptr: " << n << std::endl;
    return ptr;
}

int main() {
    auto ptr = get_int_ptr(3);
    std::cout << "*ptr: " << *ptr << std::endl;
    return 0;
}
