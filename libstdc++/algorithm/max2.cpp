// max example
#include <iostream>     // std::cout
#include <algorithm>    // std::max

int main () {
  float dist1 = 1.0;
  float dist2 = 2.0;
  float dist3 = 3.0;
  float dist4 = 4.0;
  
  float max_dist = std::max({dist1, dist2, dist3, dist4});
  std::cout << "max_dist: " << max_dist << std::endl;

  return 0;
}

/*
Output:
max_max: 4.0
*/
