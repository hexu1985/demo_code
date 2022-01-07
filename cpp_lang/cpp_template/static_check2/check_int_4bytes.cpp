#include "static_check.h"

LOKI_STATIC_CHECK(sizeof(int) == 4, sizeof_int_should_4_bytes_in_This_machine);
int main() { return 0; }
