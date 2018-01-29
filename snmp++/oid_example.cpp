#include <iostream>
#include "snmp_pp/oid.h" 

using namespace std;
using namespace Snmp_pp;

void oid_example() 
{ 
    // construct an Oid with a dotted string and print it out 
    Oid o1("1.2.3.4.5.6.7.8.9.1"); 
    cout << "o1= " << o1.get_printable() << '\n'; // construct an Oid with another Oid and print it out 
    Oid o2(o1); 
    cout << "o2= " << o2.get_printable() << '\n';

    // trim o2's last value and print it out 
    o2.trim(1); 
    cout << "o2= " << o2.get_printable() << '\n'; 
    
    // add a 2 value to the end of o2 and print it out 
    o2+=2; 
    cout << "o2= " << o2.get_printable() << '\n'; 
    
    // create a new Oid, o3 
    Oid o3; 
    // assign o3 a value and print it out 
    o3="1.2.3.4.5.6.7.8.9.3"; 
    cout << "o3= " << o3.get_printable() << '\n'; 
    
    // create o4 
    Oid o4; 

    // assign o4 o1's value 
    o4=o1; 
    
    // trim off o4 by 1 
    o4.trim(1); 

    // concat a 4 onto o4 and print it out 
    o4+=".4"; 
    cout << "o4= " << o4.get_printable() << '\n'; 
    
    // make o5 from o1 and print it out 
    Oid o5(o1); 
    cout << "o5= " << o5.get_printable() << '\n'; 
    // compare two not equal oids 
    if (o1==o2) cout << "O1 EQUALS O2" << '\n'; 
    else cout << "o1 not equal to o2" << '\n'; 
    
    // print out a piece of o1 
    cout << "strval(3) of O1 = " << o1.get_printable(3) << '\n'; 

    // print out a piece of o1
    cout << "strval(1,3) of O1 = " << o1.get_printable(1,3) << '\n'; 

    // set o1's last subid 
    o1[ o1.len()-1] = 49; 
    cout << "O1 modified = " << o1.get_printable() << '\n'; 
    
    // set o1's 3rd subid 
    o1[2]=49; 
    cout << "O1 modified = " << o1.get_printable() << '\n'; 
    
    // get the last subid of 02 
    cout << "last of o2 = " << o2[o2.len()-1] << '\n'; 
    
    // get the 3rd subid of 02 
    cout << "3rd of o2 = " << o2[2] << '\n'; 
    
    // ncompare 
    if (o1.nCompare(3,o2)) 
        cout << "nCompare o1,o2,3 ==" << '\n'; 
    else 
        cout << "nCompare o1,o2,3 !=" << '\n'; 
    
    // make an array of oids 
    Oid oids[30]; int w; 
    for ( w=0;w<30;w++) { 
        oids[w] = "300.301.302.303.304.305.306.307"; 
        oids[w] += (w+1); 
    } 
    for (w=0;w<25;w++) { 
        char msg[1024] = {0};
        sprintf( msg,"Oids[%d] = %s\n",w, oids[w].get_printable()); 
        printf("%s\n",msg); 
    } 
}

int main(int argc, char *argv[])
{
    oid_example();
}
