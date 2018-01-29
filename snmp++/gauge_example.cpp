// Gauge Examples 
#include <iostream>
#include "snmp_pp/gauge.h" 

using namespace std;
using namespace Snmp_pp;

void gauge_example() 
{ 
    Gauge32 gge ; // create an un-initialized Gauge instance 
    Gauge32 gge1( (unsigned long) 57); // create a Gauge using a number 
    Gauge32 gge2(gge1); // create a Gauge using another instance 
    
    gge = 192; // overloaded assignment to a number 
    gge1 = gge; // overloaded assignment to another counter 
    cout << (unsigned long) gge << '\n'; // behave like an unsigned long int 
} // end gauge example 12. Counter64

int main(int argc, char *argv[]) 
{
    gauge_example();
}
