// ratio example
#include <iostream>
#include <ratio>

int main ()
{
  typedef std::ratio<1,3> one_third;
  typedef std::ratio<2,4> two_fourths;

  std::cout << "one_third= " << one_third::num << "/" << one_third::den << std::endl;
  std::cout << "two_fourths= " << two_fourths::num << "/" << two_fourths::den << std::endl;

  typedef std::ratio_add<one_third,two_fourths> sum;

  std::cout << "sum= " << sum::num << "/" << sum::den;
  std::cout << " (which is: " << ( double(sum::num) / sum::den ) << ")" << std::endl;

  std::cout << "1 kilogram has " << ( std::kilo::num / std::kilo::den ) << " grams";
  std::cout << std::endl;

  return 0;
}

/*
Output:
one_third= 1/3
two_fourths= 1/2
sum= 5/6 (which is 0.833333)
1 kilogram has 1000 grams
*/
