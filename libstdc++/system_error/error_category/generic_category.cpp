#include <system_error>   // std::is_error_condition_enum, std::error_category,
#include <iostream>
#include <string.h>

int main()
{
    auto &category = std::generic_category();
    for (int i = 0; i < 255; i++) {
        std::cout << "errno(" << i << "): " << category.message(i) << std::endl;
    }

    return 0;
}
