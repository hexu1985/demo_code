// duration_cast
#include <iostream>     // std::cout
#include <chrono>       // std::chrono::seconds, std::chrono::milliseconds
                        // std::chrono::duration_cast

int main ()
{
  std::chrono::milliseconds ms = std::chrono::milliseconds(2500);  // 2500 millisecond

  double s = std::chrono::duration<double>(ms).count();   // truncated

  std::cout << "ms: " << ms.count() << std::endl;
  std::cout << "s: " << s << std::endl;

  return 0;
}

/*
Output:
ms: 2500
s: 2.5
*/
