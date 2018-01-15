#include <iostream>
#include <string>

#include "Typelist.h"

using namespace Loki;

template <typename TList, template <typename> class Unit>
class GenScatterHierarchy;

template <typename T1, typename T2, template <typename> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
    , public GenScatterHierarchy<T2, Unit> {
};

template <typename AtomicType, template <typename> class Unit>
class GenScatterHierarchy: public Unit<AtomicType> {
};

template <template <typename> class Unit>
class GenScatterHierarchy<NullType, Unit> {
};

template <typename T>
struct Holder {
    T value_;
};

// typedef GenScatterHierarchy<LOKI_TYPELIST_3(std::string, double, std::string), Holder> TestInfo;
// 当出现多个相同型别时, 会有二义性问题
typedef GenScatterHierarchy<LOKI_TYPELIST_3(int, double, std::string), Holder> TestInfo;

int main(int argc, char *argv[])
{
    TestInfo obj;
    (static_cast<Holder<std::string> &>(obj)).value_ = "hello world";
    std::string name = (static_cast<Holder<std::string> &>(obj)).value_;
    std::cout << name << std::endl;
    return 0;
}
