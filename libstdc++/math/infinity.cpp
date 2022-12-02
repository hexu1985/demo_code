#include <iostream>
#include <limits>
#include <cmath>

int main()
{
    double max = std::numeric_limits<double>::max();
    double inf = INFINITY;
 
    if(inf > max)
        std::cout << inf << " is greater than " << max << '\n';
}
