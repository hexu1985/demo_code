// Counter64 examples 
#include <iostream>
#include "snmp_pp/ctr64.h" 

using namespace std;
using namespace Snmp_pp;

void counter64_example() 
{ 
    Counter64 c64; // instantiate a 64 bit counter object with no parms 
    Counter64 my_c64( 100, 100); // instantiate a 64 bit counter with a hi and low value 
    Counter64 your_c64( my_c64); // instantiate a 64 counter using another 64bit counter 
    
    cout << my_c64.high() << '\n'; // print out the high portion of the c64 
    cout << my_c64.low() << '\n'; // print out the low portion of the c64 
    cout << my_c64.get_printable() << '\n';
    
    c64 = my_c64 + your_c64; // overloaded addition 
    c64 = my_c64 * your_c64; // overloaded multiplication 
    c64 = my_c64 / your_c64; // overloaded division 
    c64 = my_c64 - your_c64; // overloaded subtraction 
    
    if ( c64 == my_c64) // overloaded equivalence test 
        cout << "c64 equals my_c64\n"; 
    
    if ( c64 != my_c64) // overloaded not equal test 
        cout << "c64 not equal to my_c64\n"; 
    
    if ( c64 < my_c64) // overloaded less than 
        cout << "c64 less than my_c64\n";
} // end Counter64 example

int main(int argc, char *argv[])
{
    counter64_example();
}
