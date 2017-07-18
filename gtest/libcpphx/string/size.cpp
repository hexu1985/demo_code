// string::size
#include "test_string.h"
#include <iostream>

TEST(Test_string, size)
{
  string str ("Test string");

  EXPECT_EQ(str.size(), 11);

  std::cout << "The size of str is " << str.size() << " characters.\n";
}

/*	
Edit & Run


Output:

The size of str is 11 characters
*/
