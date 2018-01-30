#include <iostream>
#include "snmp_pp/snmp_pp.h"  

#define SYSCONTACT "1.3.6.1.2.1.1.4.0" // Object ID for system contact 
#define SYSNAME "1.3.6.1.2.1.1.5.0" // Object ID for system name 
#define SYSLOCATION "1.3.6.1.2.1.1.6.0" // Object ID for system location

using namespace std;
using namespace Snmp_pp;

void multi_set() { 
    int status; // return status 
    CTarget ctarget( (IpAddress) "10.4.8.5"); // SNMP++ v1 target 
    Vb vb[3]; // a vb for each object to get 
    Pdu pdu; // SNMP++ PDU 
    
    //-------[ Construct a SNMP++ SNMP Object ]--------------------------------------- 
    Snmp snmp( status); // Create a SNMP++ session 
    if ( status != SNMP_CLASS_SUCCESS) { // check creation status 
        cout << snmp.error_msg( status) << '\n'; // if fail, print error string 
        return; 
    } 
    
    //-------[ build up the vbs to get]----------------------------------------------------------------- 
    vb[0].set_oid( SYSCONTACT); 
    vb[0].set_value("Alan Turing"); 
    vb[1].set_oid( SYSNAME); 
    vb[1].set_value(" The Turing Machine"); 
    vb[2].set_oid( SYSLOCATION ); 
    vb[2].set_value(" Cambridge, UK"); 
    
    //----[ append all the vbs to the pdu ]----------------------------------------------------- 
    for ( int z=0;z<3;z++) 
        pdu += vb[z]; 
    
    //-------[ Invoke a SNMP++ Set ]------------------------------------------------------- 
    status = snmp.set( pdu, ctarget); 
    cout << snmp.error_msg( status) << '\n'; 
}

int main(int argc, char *argv[]) 
{
    multi_set();
}

