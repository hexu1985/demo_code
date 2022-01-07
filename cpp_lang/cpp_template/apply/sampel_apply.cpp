// ------------- UTILITY---------------
template<int...> struct index_tuple{}; 

template<int I, typename IndexTuple, typename... Types> 
struct make_indexes_impl; 

template<int I, int... Indexes, typename T, typename ... Types> 
struct make_indexes_impl<I, index_tuple<Indexes...>, T, Types...> 
{ 
    typedef typename make_indexes_impl<I + 1, index_tuple<Indexes..., I>, Types...>::type type; 
}; 

template<int I, int... Indexes> 
struct make_indexes_impl<I, index_tuple<Indexes...> > 
{ 
    typedef index_tuple<Indexes...> type; 
}; 

template<typename ... Types> 
struct make_indexes : make_indexes_impl<0, index_tuple<>, Types...> 
{}; 

 // ----------UNPACK TUPLE AND APPLY TO FUNCTION ---------
#include <tuple>
#include <iostream> 

using namespace std;

template<class Ret, class... Args, int... Indexes > 
Ret apply_helper( Ret (*pf)(Args...), index_tuple< Indexes... >, tuple<Args...>&& tup) 
{ 
    return pf( forward<Args>( get<Indexes>(tup))... ); 
} 

template<class Ret, class ... Args> 
Ret apply(Ret (*pf)(Args...), const tuple<Args...>&  tup)
{
    return apply_helper(pf, typename make_indexes<Args...>::type(), tuple<Args...>(tup));
}

template<class Ret, class ... Args> 
Ret apply(Ret (*pf)(Args...), tuple<Args...>&&  tup)
{
    return apply_helper(pf, typename make_indexes<Args...>::type(), forward<tuple<Args...>>(tup));
}

// --------------------- TEST ------------------
void one(int i, double d)
{
    std::cout << "function one(" << i << ", " << d << ");\n";
}
int two(int i)
{
    std::cout << "function two(" << i << ");\n";
    return i;
}

int main()
{
    std::tuple<int, double> tup(23, 4.5);
    apply(one, tup);

    int d = apply(two, std::make_tuple(2));    

    return 0;
}
