#include <iostream>
#include "snmp_pp/snmp_pp.h"  

#define SYSLOCATION "1.3.6.1.2.1.1.6.0" // Object ID for System location 

using namespace std;
using namespace Snmp_pp;

void set_system_location() 
{ 
    int status; // return status 
    CTarget ctarget( (IpAddress) "127.0.0.1"); // SNMP++ v1 target 
    Vb vb( SYSLOCATION); // SNMP++ Variable Binding 
    Pdu pdu; // SNMP++ PDU 
    
    //-------[ Construct a SNMP++ SNMP Object ]--------------------------------------- 
    Snmp snmp( status); // Create a SNMP++ session 
    if ( status != SNMP_CLASS_SUCCESS) { // check creation status 
        cout << snmp.error_msg( status); // if fail, print error string 
        return; 
    } 
    
    //-------[ Invoke a SNMP++ Set ]------------------------------------------------------- 
    vb.set_value("Upstairs Mezzanine"); // add location string to vb 
    pdu += vb; // add the variable binding 
    status = snmp.set( pdu, ctarget); 
    cout << snmp.error_msg(status) << '\n'; 
}

int main(int argc, char *argv[]) 
{
    set_system_location();
}
