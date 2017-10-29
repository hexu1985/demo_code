#include <iostream>

using namespace std;

class Float {
public:
    Float(float a)
    {
        std::cerr << "Float(double a)\n";
    }

    Float(const Float &a)
    {
        std::cerr << "Float(const Float &a)\n";
    }
};

int main()
{
    Float a = 3.0;
}

