#include <iostream>
#include "snmp_pp/vb.h" 
#include "snmp_pp/pdu.h" 
#include "snmp_pp/uxsnmp.h" 

using namespace std;
using namespace Snmp_pp;

#define SYSDESCR "1.3.6.1.2.1.1.1.0" // Object ID for System Descriptor

// example of how to unload a Pdu 
void unload_pdu_example() 
{ 
    int status; 
    Pdu pdu; // create a Pdu object 
    Vb vb; // create a Vb object 
    vb.set_oid( SYSDESCR); // set the oid portion of the Vb to System Descriptor 
    pdu += vb; // loads the Vb to the Pdu 
    char message[100]; // for the system descriptor printable octet 
    
    Snmp snmp( status); 
    if ( status != SNMP_CLASS_SUCCESS) { 
        cout << "SNMP++ error = " << snmp.error_msg( status) << '\n'; 
        return; 
    } 
    
    pdu.get_vb( vb,0); // unload the vb 
    vb.get_value( message); // pull the message out of the vb 
    cout << message; // print it out 
}


int main(int argc, char *argv[]) 
{
    unload_pdu_example();
}

