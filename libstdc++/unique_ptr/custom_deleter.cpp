#include <memory>
#include <cstdlib>

template <typename T>
class malloc_deleter {
public:
    void operator()(T* ptr) const {
        free(ptr);
    }
};

int main()
{
    std::unique_ptr<int> u1(new int[5]);
    std::unique_ptr<int, malloc_deleter<int>> u2(new int[5]);
    std::unique_ptr<int[], malloc_deleter<int>> u3(new int[5]);
}
