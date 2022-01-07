#include <iostream>
#include <tuple>

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
