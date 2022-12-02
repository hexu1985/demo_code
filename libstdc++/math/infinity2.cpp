#include <iostream>
#include <limits>
#include <cmath>

int main()
{
    float max = std::numeric_limits<float>::max();
    float inf = INFINITY;
 
    if(inf > max)
        std::cout << inf << " is greater than " << max << '\n';
}
