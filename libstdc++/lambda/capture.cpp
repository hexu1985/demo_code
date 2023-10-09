#include <iostream>

struct Record {
    int i_val;
    std::string s_val;
    double d_val;
};

int main() {
    Record record;
    record.i_val = 1;
    record.s_val = "first";
    record.d_val = 1.0;

    auto print_func = [i_val=record.i_val, s_val=record.s_val, d_val=record.d_val]() {
        std::cout << "i_val: " << i_val << ", " 
                    << "s_val: " << s_val << ", "
                    << "d_val: " << d_val << ", " << std::endl;
    };

    record.i_val = 12;
    record.s_val = "twelve";
    record.d_val = 12.0;

    print_func();
    return 0;
}
