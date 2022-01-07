#include "static_check.h"

LOKI_STATIC_CHECK(sizeof(int) == 8, sizeof_int_should_8_bytes_in_This_machine);
int main() { return 0; }
