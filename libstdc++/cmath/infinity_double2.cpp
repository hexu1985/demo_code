#include <iostream>
#include <limits>
#include <cmath>

union Double {
    double val;
    uint8_t raw[sizeof(double)];
};


int main()
{
    Double max; max.val = std::numeric_limits<double>::max();
    Double inf; inf.val = INFINITY;
 
    if(inf.val > max.val)
        std::cout << inf.val << " is greater than " << max.val << '\n';
}
