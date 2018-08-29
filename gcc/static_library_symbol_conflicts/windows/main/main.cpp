#include <iostream>
void DoThing();
void DoLayer();

int main()
{
  printf("start \n");
  DoThing();
  DoLayer();
  printf("finished \n");
  char c;
  std::cin >> c;
  return 0;
}
