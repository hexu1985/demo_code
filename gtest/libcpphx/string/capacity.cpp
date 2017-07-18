// comparing size, length, capacity and max_size
#include "test_string.h"
#include <iostream>

TEST(Test_string, capacity)
{
  string str ("Test string");

  EXPECT_EQ(str.size(), 11);
  EXPECT_EQ(str.length(), 11);
  EXPECT_GE(str.capacity(), 11);

  std::cout << "size: " << str.size() << "\n";
  std::cout << "length: " << str.length() << "\n";
  std::cout << "capacity: " << str.capacity() << "\n";
  std::cout << "max_size: " << str.max_size() << "\n";
}

/*	
Edit & Run


A possible output for this program could be:

size: 11
length: 11
capacity: 15
max_size: 429496729
*/
