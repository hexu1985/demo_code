#include <iostream>
#include "snmp_pp/snmp_pp.h"  

#define SYSDESCR "1.3.6.1.2.1.1.1.0" // Object ID for system descriptor 
#define SYSOBJECTID "1.3.6.1.2.1.1.2.0" // Object ID for system object ID 
#define SYSUPTIME "1.3.6.1.2.1.1.3.0" // Object ID for system up time 
#define SYSCONTACT "1.3.6.1.2.1.1.4.0" // Object ID for system contact 
#define SYSNAME "1.3.6.1.2.1.1.5.0" // Object ID for system name

using namespace std;
using namespace Snmp_pp;

void get_system_group() 
{ 
    int status; // return status 
    CTarget ctarget( (IpAddress) "127.0.0.1"); // SNMP++ v1 target 
    Vb vb[5]; // a vb for each object to get 
    Pdu pdu; // SNMP++ PDU 
    
    //-------[ Construct a SNMP++ SNMP Object ]--------------------------------------- 
    Snmp snmp( status); // Create a SNMP++ session 
    if ( status != SNMP_CLASS_SUCCESS) { // check creation status 
        cout << snmp.error_msg( status) << '\n'; // if fail, print error string 
        return; 
    } 
    
    //-------[ build up the vbs to get]-----------------------------------------------------------------
    vb[0].set_oid( SYSDESCR); 
    vb[1].set_oid( SYSOBJECTID); 
    vb[2].set_oid( SYSUPTIME); 
    vb[3].set_oid(SYSCONTACT); 
    vb[4].set_oid( SYSNAME); 
    
    //----[ append all the vbs to the pdu ]----------------------------------------------------- 
    for ( int z=0;z<5;z++) 
        pdu += vb[z]; 
    
    //-------[ Invoke a SNMP++ Get ]------------------------------------------------------- 
    if ( (status = snmp.get( pdu, ctarget)) != SNMP_CLASS_SUCCESS) 
        cout << snmp.error_msg( status) << '\n'; 
    else { 
        pdu.get_vblist( vb,5); // extract the variable bindings
        for ( int w=0;w<5;w++) 
            cout << vb[w].get_printable_value() << "\n"; 
    } // print out the value 
}

int main(int argc, char *argv[]) 
{
    get_system_group();
}
