#include <iostream>
#include "snmp_pp/snmp_pp.h"  

#define SYSDESCR "1.3.6.1.2.1.1.1.0" // Object ID for System Descriptor 

using namespace std;
using namespace Snmp_pp;

void get_system_descriptor() 
{ 
    int status; // return status 
    CTarget ctarget( (IpAddress) "127.0.0.1"); // SNMP++ community target 
    
    Vb vb( SYSDESCR); // SNMP++ Variable Binding Object 
    Pdu pdu; // SNMP++ PDU 
    
    //-------[ Construct a SNMP++ SNMP Object ]--------------------------------------- 
    Snmp snmp( status); // Create a SNMP++ session
    if ( status != SNMP_CLASS_SUCCESS) { // check creation status 
        cout << snmp.error_msg( status) << endl; // if fail, print error string 
        return; 
    }

    //-------[ Invoke a SNMP++ Get ]------------------------------------------------------- 
    pdu += vb; // add the variable binding to the PDU 
    if ( (status = snmp.get( pdu, ctarget)) != SNMP_CLASS_SUCCESS) 
        cout << snmp.error_msg( status) << endl; 
    else { 
        pdu.get_vb( vb,0); // extract the variable binding from PDU 
        cout << "System Descriptor = "<< vb.get_printable_value() << endl; 
    } // print out the value 
} // Thats all!

int main(int argc, char *argv[]) 
{
    get_system_descriptor();
}
