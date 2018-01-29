#include <iostream>
#include "snmp_pp/oid.h" 
#include "snmp_pp/vb.h" 

using namespace std;
using namespace Snmp_pp;

void vb_test() 
{ 
    // -------[Ways to construct Vb objects ]------- 
    // construct a single Vb object 
    Vb vb1; 
    
    // construct a Vb object with an Oid object 
    // this sets the Oid portion of the Vb 
    Oid d1("1.3.6.1.4.12"); 
    Vb vb2(d1); 
    
    // construct a Vb object with a dotted string 
    Vb vb3( (Oid) "1.2.3.4.5.6"); 
    
    // construct an array of ten Vbs 
    Vb vbs[10]; 
    
    //------[Ways to set and get the Oid portion of Vb objects ] 

    // set and get the Oid portion 
    Oid d2((Oid)"1.2.3.4.5.6"); 
    vb1.set_oid(d2); 
    Oid d3; 
    vb1.get_oid(d3); 
    if (d2==d3) cout << "They better be equal!!\n";

    Vb ten_vbs[10]; 
    int z; 
    for (z=0;z<10;z++) 
        ten_vbs[z].set_oid((Oid)"1.2.3.4.5"); 
    
    //-------[ ways to set and get values ] 
    // set & get ints 
    int x,y; 
    x=5; 
    vb1.set_value(x); 
    vb1.get_value(y); 
    if ( x == y) cout << "x equals y\n"; 

    // set and get long ints 
    long int a,b; 
    a=100; 
    vbs[0].set_value( a); vbs[0].get_value( b);

    //-------[ ways to set and get values ] 
    if ( a == b) cout << "a equals b\n"; 

    // set & get unsigned long ints 
    unsigned long int c,d; c = 1000; 
    vbs[0].set_value( c); vbs[0].get_value( d); 
    if ( c == d) cout << "c equals d\n"; 
    
    // set a 64 bit counter 
    Counter64 c64(1000,1001); vbs[1].set_value( c64); 
    
    // get and set an oid as a value 
    Oid o1, o2; 
    o1 = "1.2.3.4.5.6"; 
    vbs[2].set_value( o1); vbs[2].get_value( o2); 
    if ( o1 == o2) cout << "o1 equals o2\n"; 
    
    // set and get an octet string
    unsigned char data[4],outdata[4]; 
    unsigned long len,outlen; 
    len =4; data[0] = 10; data[1] = 12; data[2] = 12; data[3] = 13; 
    OctetStr octetstr(data,len); 
    vbs[3].set_value( octetstr); 
    vbs[3].get_value( octetstr); 
    
    // get & set a string 
    char beer[80]; char good_beer[80]; 
    strcpy( beer,"Sierra Nevada Pale Ale"); 
    vbs[4].set_value( beer); 
    vbs[4].get_value( good_beer); 
    printf("Good Beer = %s\n",good_beer); 
    // get and set an ip an address 
    IpAddress ipaddress1, ipaddress2; 
    ipaddress1 = "10.4.8.5"; 
    vbs[5].set_value( ipaddress1); 
    vbs[5].get_value( ipaddress2); 
    cout << ipaddress2; 
} // end vb example

int main(int argc, char *argv[]) 
{
    vb_test();
}
