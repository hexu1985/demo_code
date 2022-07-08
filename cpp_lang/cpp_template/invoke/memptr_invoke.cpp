#include <iostream>

// a class with data members:
struct MyValue {
  int value;
  int fifth() {return value/5;}
};

template <typename MT1, typename B, typename T>
void memptr_inovke(MT1 B::*pmf, T&& t, const std::string& desc)
{
    std::cout << "call " << desc << std::endl;
}

int main(int argc, char* argv[])
{
    MyValue sixty {60};

    memptr_inovke(&MyValue::value, sixty, "MyValue::value");
    memptr_inovke(&MyValue::fifth, sixty, "MyValue::fifth()");
    return 0;
}

