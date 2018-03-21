#include <boost/optional.hpp>
#include <iostream>
#include <cstdlib>
 
boost::optional<const char*> maybe_getenv(const char* n)
{
    if(const char* x = std::getenv(n))
       return x;
    else
       return {};
}
int main()
{
     std::cout << maybe_getenv("MYPWD").value_or("(none)") << '\n';
}
