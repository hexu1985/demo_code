// string constructor
#include <iostream>
#include "String.h"

using String = jd::String;

int main ()
{
  String s0 ("Initial string");

  // constructors used in the same order as described above:
  String s1;
  String s2 (s0);
  String s3 (s0, 8, 3);
  String s4 ("A character sequence");
  String s5 ("Another character sequence", 12);
  String s6a (10, 'x');
  String s6b (10, 42);      // 42 is the ASCII code for '*'
  String s7 (s0.begin(), s0.begin()+7);

  std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
  std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6a: " << s6a;
  std::cout << "\ns6b: " << s6b << "\ns7: " << s7 << '\n';
  return 0;
}

	
/*
Output:

s1: 
s2: Initial string
s3: str
s4: A character sequence
s5: Another char
s6a: xxxxxxxxxx
s6b: **********
s7: Initial
*/
