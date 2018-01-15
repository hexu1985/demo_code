#include <iostream>
#include <string>

#include "Typelist.h"

using namespace Loki;
using namespace Loki::TL;

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

template <typename TList, template <typename> class Unit>
Unit<typename TList::Head> &FieldHelper(
        GenScatterHierarchy<TList, Unit> &obj,
        Int2Type<0>)
{
    GenScatterHierarchy<typename TList::Head, Unit> &leftBase = obj;
    return leftBase;
}

template <int i, typename TList, template <typename> class Unit>
Unit<typename TypeAt<TList, i>::Result> &FieldHelper(
        GenScatterHierarchy<TList, Unit> &obj,
        Int2Type<i>)
{
    GenScatterHierarchy<typename TList::Tail, Unit> &rightBase = obj;
    return FieldHelper(rightBase, Int2Type<i-1>());
}

template <int i, typename TList, template <typename> class Unit>
Unit<typename TypeAt<TList, i>::Result> &
Field(GenScatterHierarchy<TList, Unit> &obj)
{
    return FieldHelper(obj, Int2Type<i>());
}

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
    Field<2>(obj).value_ = "hello world";
    std::string name = Field<2>(obj).value_;
    std::cout << name << std::endl;
    return 0;
}
