// string assigning
#include "test_string.h"
#include <iostream>

TEST(Test_string, assigning)
{
  string str1, str2, str3;
  str1 = "Test string: ";   // c-string
  str2 = 'x';               // single character
  str3 = str1 + str2;       // string

  EXPECT_EQ(str3, "Test string: x");
  EXPECT_STREQ(str3.c_str(), "Test string: x");

  std::cout << str3  << '\n';
}

/**
Edit & Run


Output:

Test string: x
*/
