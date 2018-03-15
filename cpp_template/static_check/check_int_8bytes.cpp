#include "static_check.h"

int main() 
{ 
    LOKI_STATIC_CHECK(sizeof(int) == 8, sizeof_int_should_8_bytes_in_This_machine);
    return 0; 
}
