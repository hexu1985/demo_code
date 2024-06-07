
#include <iostream>

template <typename T>
class MemoryBlock {
public:
    constexpr static size_t PAGE_SIZE = 4096;
    constexpr static size_t N = (PAGE_SIZE > sizeof(T)) ? (PAGE_SIZE / sizeof(T)) : 1;

    T data[N];
};


int main() 
{
    MemoryBlock<int> block;
    std::cout << sizeof(block) << std::endl;
    std::cout << block.N << std::endl;

    return 0;
}


