// resizing string
#include "test_string.h"
#include <iostream>

TEST(Test_string, resize)
{
  string str ("I like to code in C");

  EXPECT_EQ(str, "I like to code in C");
  EXPECT_STREQ(str.c_str(), "I like to code in C");
  EXPECT_EQ(str.size(), 19);

  std::cout << str << '\n';

  string::size_type sz = str.size();

  str.resize (sz+2,'+');

  EXPECT_EQ(str, "I like to code in C++");
  EXPECT_STREQ(str.c_str(), "I like to code in C++");
  EXPECT_EQ(str.size(), 21);

  std::cout << str << '\n';

  str.resize (14);

  EXPECT_EQ(str, "I like to code");
  EXPECT_STREQ(str.c_str(), "I like to code");
  EXPECT_EQ(str.size(), 14);

  std::cout << str << '\n';
}

/*	
Edit & Run


Output:

I like to code in C
I like to code in C++
I like to code
*/
