#include <memory>
#include <cstdlib>
#include <iostream>

template <typename T>
class malloc_deleter {
public:
    void operator()(T* ptr) const {
        std::cout << "free from malloc_deleter<T>" << std::endl;
        free(ptr);
    }
};

template <typename T>
class malloc_deleter<T[]> {
public:
    void operator()(T* ptr) const {
        std::cout << "free from malloc_deleter<T[]>" << std::endl;
        free(ptr);
    }
};

int main()
{
    std::unique_ptr<int> u1(new int[5]);                // error: alloc_dealloc_mismatch
    std::unique_ptr<int, malloc_deleter<int>> u2(new int[5]);   // error: alloc_dealloc_mismatch
    std::unique_ptr<int, malloc_deleter<int>> u3((int*)malloc(sizeof(int)*5));
    std::unique_ptr<int[], malloc_deleter<int>> u4((int*)malloc(sizeof(int)*5));
    std::unique_ptr<int[], malloc_deleter<int[]>> u5((int*)malloc(sizeof(int)*5));
}
