#include <iostream>
#include <string>

#include "Typelist.h"

using namespace Loki;
using namespace Loki::TL;

// is not reachable in any way!
template<class, class> 
struct ScatterHierarchyTag;

template <typename TList, template <typename> class Unit>
class GenScatterHierarchy;
 
template <typename T1, typename T2, template <typename> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
    : public GenScatterHierarchy<ScatterHierarchyTag<T1, T2>, Unit>
    , public GenScatterHierarchy<T2, Unit>
{
public:
    typedef Typelist<T1, T2> TList;
    // Insure that LeftBase is unique and therefore reachable
    typedef GenScatterHierarchy<ScatterHierarchyTag<T1, T2>, Unit> LeftBase;
    typedef GenScatterHierarchy<T2, Unit> RightBase;
    template <typename T> struct Rebind
    {
        typedef Unit<T> Result;
    };
};
 
// In the middle *unique* class that resolve possible ambiguity
template <typename T1, typename T2, template <typename> class Unit>
class GenScatterHierarchy<ScatterHierarchyTag<T1, T2>, Unit> 
    : public GenScatterHierarchy<T1, Unit>
{
};

template <typename AtomicType, template <typename> class Unit>
class GenScatterHierarchy : public Unit<AtomicType>
{
    typedef Unit<AtomicType> LeftBase;
    template <typename T> struct Rebind
    {
        typedef Unit<T> Result;
    };
};

template <template <typename> class Unit>
class GenScatterHierarchy<NullType, Unit>
{
    template <typename T> struct Rebind
    {
        typedef Unit<T> Result;
    };
};

template <typename TList, template <typename> class Unit>
Unit<typename TList::Head> &FieldHelper(
        GenScatterHierarchy<TList, Unit> &obj,
        Int2Type<0>)
{
    typename GenScatterHierarchy<TList, Unit>::LeftBase &leftBase = obj;
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

typedef GenScatterHierarchy<LOKI_TYPELIST_3(std::string, double, std::string), Holder> TestInfo;

int main(int argc, char *argv[])
{
    TestInfo obj;
    Field<0>(obj).value_ = "hello";
    Field<1>(obj).value_ = 0.0;
    Field<2>(obj).value_ = "world";
    std::string name = Field<0>(obj).value_ + " " + Field<2>(obj).value_;
    std::cout << name << std::endl;
    return 0;
}
