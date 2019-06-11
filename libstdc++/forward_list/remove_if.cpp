#include <forward_list>
#include <iostream>
 
int main()
{
    std::forward_list<int> l = { 1,100,2,3,10,1,11,-1,12 };
 
	int count = 0;
    l.remove_if([&count](int n){ if (n == 1) { count++; return true; } else return false; }); // remove all elements greater than 10
	std::cout << "number of 1 be removed from list: " << count << std::endl;
 
    for (int n : l) {
        std::cout << n << ' '; 
    }
    std::cout << '\n';
}
