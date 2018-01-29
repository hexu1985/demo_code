// Octet Class Examples 
#include <iostream>
#include "snmp_pp/octet.h" 

using namespace std;
using namespace Snmp_pp;

void octet_example() 
{ 
    OctetStr octet1; // create an invalid un- initialized octet object 
    OctetStr octet2( "Red Hook Extra Bitter Ale"); // create an octet with a string 
    OctetStr octet3( octet2); // create an octet with another octet 
    unsigned char raw_data[50]; // create some raw data 
    OctetStr octet4( raw_data, 50); // create an OctetStr using unsigned char data 
    
    octet1 = "Sierra Nevada Pale Ale"; // assign one octet to another 
    cout << octet1.get_printable() << '\n'; // show octet1 as a null terminated string 
    cout << octet2.get_printable_hex() << '\n'; // show octet2 as a hex string 
    cout << octet4.get_printable_hex() << '\n'; // show octet4 as a hex string 
//    cout << (char *) octet1 << '\n'; // same as get_printable() 
    if ( octet1 == octet2) // compare two octets 
        cout << "octet1 is equal to octet2" << '\n'; 
    else
        cout << "octet1 is not equal to octet2" << '\n'; 
    
    octet2 += "WinterFest Ale"; // concat a string to an Octet 
    if ( octet2 >= octet3) cout << "octet2 greater than or equal to octet3" << '\n'; 
    
    octet2[4] = 'b'; // modify an element of an OctetStr using [ ]'s 

    cout << octet1.len() << '\n'; // print out the length of an OctetStr 

    unsigned char raw_data2[100]; 
    octet1.set_data( raw_data2, 100); // set the data of an to unsigned char data 
    
    // get the validity of an OctetStr 
    cout << ((octet1.valid() )? "Octet1 is valid" : "Octet1 is Invalid") << '\n'; 
} // end octet example

int main(int argc, char *argv[]) 
{
    octet_example();
}

