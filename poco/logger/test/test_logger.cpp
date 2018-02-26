#include "dante_logger.h"

void Test_logger()
{
    poco_information(logger_handle , "hello world，this is a 苍原狮啸's blog");
}

int main()
{
    Setup_logger();
    Test_logger();
}
