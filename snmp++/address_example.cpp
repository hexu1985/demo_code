// address class examples 
#include <iostream>
#include "snmp_pp/address.h" 

using namespace std;
using namespace Snmp_pp;

void address_examples() 
{ 
    //--------------[ IPAddress construction ]------------------------------------------------------ 
    IpAddress ip1; // makes an invalid IpAddress object 
    IpAddress ip2("10.4.8.5"); // makes a IpAddress verifies dotted format 
    IpAddress ip3(ip2); // makes an IpAddress using another IpAddress 
    IpAddress ip4("trout.rose.hp.com"); // makes an IpAddress does DNS on string 
    
    //-------------[ IPX Address construction ]----------------------------------------------------- 
    IpxAddress ipx1; // makes an invalid IPX address
    IpxAddress ipx2("01020304:050607080900"); // makes and verifies an IPX address 
    IpxAddress ipx3( ipx2); // makes an IPX from another IPX 
    
    //--------------[ MAC Address construction ]----------------------------------------------------- 
    MacAddress mac1; // makes an invalid MAC address 
    MacAddress mac2("08:09:12:34:52:12"); // makes and verifies a MAC address 
    MacAddress mac3( mac2); // makes a MAC from another MAC 
    
    //---------------[ Gen Address Construction ]----------------------------------------------------- 
    GenAddress addr1("10.4.8.5"); 
    GenAddress addr2("01020304:050607080900"); 
    
    //--------------[ printing addresses ]---------------------------------------------------------------- 
#if 0
    cout << (char *) ip2 << '\n'; 
    cout << (char *) ipx2 << '\n'; 
    cout << (char *) mac2 << '\n'; 
#endif
    cout << ip2.get_printable() << '\n'; 
    cout << ipx2.get_printable() << '\n'; 
    cout << mac2.get_printable() << '\n'; 
    
    //---------------[ assigning Addresses ]------------------------------------------------------------ 
    ip1 = "15.29.33.10"; 
    ipx1 = "00000001-080912345212"; 
    mac1 = "08:09:12:34:52:12"; 
    
    //--------------[ comparing Addresses ]---------------------------------------------------------- 
    if ( ip1 == ip2) 
        cout << "ip1 == ip2" << '\n'; 
    
    if (ipx1 != ipx2) 
        cout << "ipx1 != ipx2" << '\n'; 
    
    if ( mac1 <= mac2)
        cout << "mac1 < mac2" << '\n'; 
    
    //---------------[ modifying an address ]----------------------------------------------------------- 
    mac1[4] = 15; 
    cout << mac2[2]; 
} // end address examples

int main(int argc, char *argv[])
{
    address_examples();
}
