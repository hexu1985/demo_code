#ifndef MINI_UTILS_RANDOM_NUMBER_INC
#define MINI_UTILS_RANDOM_NUMBER_INC

#include <cstdint>

namespace mini_utils {

class RandomNumber {
public:
	RandomNumber(int32_t s = 1)
    {
        seed(s);
    }

    void seed(int32_t s)
    {
        if (s == 0) {
            s = 0x5EECE66DL;
        } else if (s < 0) {
            s = (s & 0x7fffffff) ^ 0x5EECE66DL;
        }

        seed_ = s;
    }

    int32_t seed() const 
    {
        return seed_;
    }

	int32_t random()
    {
        int32_t tmpSeed = A * ( seed_ % Q ) - R * ( seed_ / Q );

        if( tmpSeed >= 0 )
            seed_ = tmpSeed;
        else
            seed_ = tmpSeed + M;

        return seed_;
    }

    static int32_t min()
    {
        return 1;
    }

    static int32_t max() 
    {
        return M-1;
    }

	double frandom()
    {
        return double(random())/double(M);
    }

    double randReal(double a, double b)
    {
        return a + (b-a) * frandom();
    }

    long randInt(long a, long b)
    {
        return a + long((b-a+1) * frandom());
    }

private:
	static const int32_t A = 48271;
	static const int32_t M = 2147483647;
	static const int32_t Q = M / A;
	static const int32_t R = M % A;

	int32_t seed_;
};

}   // namespace mini_utils

#endif
