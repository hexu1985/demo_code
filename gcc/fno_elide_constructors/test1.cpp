#include <iostream>

using namespace std;

class Float {
public:
    explicit Float(float a)
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

