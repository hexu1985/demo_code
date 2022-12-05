#include <iostream>
#include <tuple>
using namespace std;

template <class Tuple, size_t N>
struct print_imp {
    static void print(ostream& out, const Tuple& t)
    {
        print_imp<Tuple, N - 1>::print(out, t);//1
        out << ", " << get<N - 1>(t);//2
    }
};

template <class Tuple>
struct print_imp<Tuple, 1> {
    static void print(ostream& out, const Tuple& t)
    {
        out << get<0>(t);
    }
};

template <class... Args>
ostream& operator<<(ostream& out, const tuple<Args...>& t)
{
    out << '(';
    print_imp<decltype(t), sizeof...(Args)>::print(out, t);
    return out << ')';
}

int main()
{
    auto t = make_tuple(12, 4.5, 3, 6.7, "efa");
    cout << t << endl;
}
