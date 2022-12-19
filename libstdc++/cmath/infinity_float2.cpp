#include <iostream>
#include <limits>
#include <cmath>
#include <cstdint>

union Float {
    float val;
    uint8_t raw[sizeof(float)];
};

int main()
{
    Float max; max.val = std::numeric_limits<float>::max();
    Float inf; inf.val = INFINITY;
 
    if(inf.val > max.val)
        std::cout << inf.val << " is greater than " << max.val << '\n';
}
