// TimeTicks Examples
#include <iostream>
#include "snmp_pp/timetick.h" 

using namespace std;
using namespace Snmp_pp;

void timeticks_example() 
{ 
    TimeTicks tt; // create an un-initialized timeticks instance 
    TimeTicks tt1( (unsigned long) 57); // create a timeticks using a number 
    TimeTicks tt2( tt1); // create a timeticks using another instance 
    
    tt = 192; // overloaded assignment to a number 
    tt2 = tt; // overloaded assignment to another timeticks 
    
    cout << tt.get_printable() << '\n'; // print out in DD days, HH:MM:SS.hh 
    cout << ( unsigned long) tt << '\n'; // print out unsigned long int value 
} // end timeticks example

int main(int argc, char *argv[]) 
{
    timeticks_example();
}
