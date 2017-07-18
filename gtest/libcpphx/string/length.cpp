// string::length
#include "test_string.h"
#include <iostream>

TEST(Test_string, length)
{
  string str ("Test string");

  EXPECT_EQ(str.length(), 11);

  std::cout << "The size of str is " << str.length() << " characters.\n";
}

/*	
Edit & Run


Output:

The size of str is 11 characters
*/
