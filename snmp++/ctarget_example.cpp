//------------[CTarget class examples ]----------------------------------------------------------------- 
#include <iostream>
#include "snmp_pp/target.h" 
#include "snmp_pp/address.h" 

using namespace std;
using namespace Snmp_pp;


// ----------[ instantiating CTarget Objects ]----------------------------- 
void ctarget_examples()
{
    // valid complete instantiation 
    CTarget ct((IpAddress)"10.10.10.10", // Address 
            "public", // read community name 
            "public"); // write community name 
    
    // valid complete using "public" defaults 
    CTarget ct2( (IpAddress) "1.2.3.4");

    // create an invalid CTarget object
    CTarget ct3;

    //----[ modifying CTargets ]------------------------------------ 
    ct.set_readcommunity("private"); // modifying the read community 
    ct.set_writecommunity("private"); // modifying the write community 
    ct.set_address( (IpAddress) "15.29.33.210");

    //-----[ Accessing CTarget member variables ]------------------------- 
    // get the write community name 
    cout << "Write community: " << ct.get_writecommunity() << '\n'; 
    
    // get the read community name 
    cout << "Read community: " << ct.get_readcommunity() << '\n'; 
    
    // get the address 
    GenAddress address; 
    ct.get_address( address); 
    
    // check the validity of a target 
    if ( ct.valid()) 
        cout << "Target is valid" << '\n';

    // create a valid CTarget using a GenAddress 
    CTarget ct4( (GenAddress) "10.20.30.40"); 
    
    // create a valid CTarget using an IpxAddress 
    IpxAddress ipxaddress("01010101-010101010101"); 
    CTarget my_target( ipxaddress); // use default "public" for communities 
    
    // create an invalid CTarget object
    CTarget ct5; // no construction params therefor invalid 
    if ( !ct5.valid()) 
        cout << "Invalid CTarget instance!" << '\n'; 
    
    // get the read community 
    cout << "Read Community =" << ct4.get_readcommunity() << '\n'; 
    
    // get the write community 
    cout << "Write Community = " << ct4.get_writecommunity() << '\n'; 
    
    // modify the get community 
    ct4.set_readcommunity( "pilsner"); 
    
    // modify the write community 
    ct4.set_writecommunity("pale ale");
}

int main(int argc, char *argv[])
{
    ctarget_examples();
}

