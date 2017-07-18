// string constructor
#include "test_string.h"
#include <iostream>

TEST(Test_string, constructor)
{
  string s0 ("Initial string");

  // constructors used in the same order as described above:
  string s1;
  string s2 (s0);
  string s3 (s0, 8, 3);
  string s4 ("A character sequence", 6);
  string s5 ("Another character sequence");
  string s6 (10, 'x');
  string s7a (10, 42);
  string s7b (s0.begin(), s0.begin()+7);

  EXPECT_NE(s1.c_str(), (char *) 0);
  EXPECT_EQ(s1, "");
  EXPECT_STREQ(s1.c_str(), "");

  EXPECT_EQ(s2, s0);
  EXPECT_EQ(s2, "Initial string");
  EXPECT_STREQ(s2.c_str(), "Initial string");

  EXPECT_EQ(s3, "str");
  EXPECT_STREQ(s3.c_str(), "str");

  EXPECT_EQ(s4, "A char");
  EXPECT_STREQ(s4.c_str(), "A char");

  EXPECT_EQ(s5, "Another character sequence");
  EXPECT_STREQ(s5.c_str(), "Another character sequence");

  EXPECT_EQ(s6, "xxxxxxxxxx");
  EXPECT_STREQ(s6.c_str(), "xxxxxxxxxx");

  EXPECT_EQ(s7a, "**********");
  EXPECT_STREQ(s7a.c_str(), "**********");

  EXPECT_EQ(s7b, "Initial");
  EXPECT_STREQ(s7b.c_str(), "Initial");

  std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
  std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6: " << s6;
  std::cout << "\ns7a: " << s7a << "\ns7b: " << s7b << '\n';
}

/*	
Edit & Run


Output:

s1: 
s2: Initial string
s3: str
s4: A char
s5: Another character sequence
s6: xxxxxxxxxx
s7a: **********
s7b: Initial
*/
