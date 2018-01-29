// Counter Examples 
#include <iostream>
#include "snmp_pp/counter.h" 

using namespace std;
using namespace Snmp_pp;

void counter_example() 
{ 
    Counter32 ctr; // create an un-initialized counter instance 
    Counter32 ctr1( (unsigned long) 57); // create a counter using a number 
    Counter32 ctr2(ctr1); // create a counter using another instance 
    
    ctr = 192; // overloaded assignment to a number 
    ctr1 = ctr; // overloaded assignment to another counter 
    cout << (unsigned long) ctr << '\n'; // behave like an unsigned long int 
} // end counter example

int main(int argc, char *argv[])
{
    counter_example();
}

