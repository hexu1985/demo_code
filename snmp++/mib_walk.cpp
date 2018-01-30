#include <iostream>
#include "snmp_pp/snmp_pp.h"  

using namespace std;
using namespace Snmp_pp;

void mib_walk() 
{
    int status; // return status 
    CTarget target( (IpAddress) "127.0.0.1"); // SNMP++ v1 target 
    Vb vb; // a SNMP++ vb 
    Pdu pdu; // SNMP++ PDU 
    
    //-------[ Construct a SNMP++ SNMP Object ]--------------------------------------- 
    Snmp snmp( status); // Create a SNMP++ session 
    if ( status != SNMP_CLASS_SUCCESS) { // check creation status 
        cout << snmp.error_msg( status) << '\n'; // if fail, print error string 
        return; 
    } 
    
    //-------[ set up the first vb ]--------------------------------------------------------------- 
    vb.set_oid("1"); // get next starting seed 
    pdu += vb; // add vb to the pdu 
    
    status = SNMP_CLASS_SUCCESS; 
    while ( status == SNMP_CLASS_SUCCESS) { 
        if ( (status = snmp.get_next( pdu, target)) == SNMP_CLASS_SUCCESS) { 
            pdu.get_vb( vb,0); // extract the vb 
            cout << "Mib Object = " << vb.get_printable_oid() << "\n"; 
            cout << "Mib Value = " << vb.get_printable_value() << "\n"; 
            pdu.set_vb( vb,0); // use last vb as the next one 
        } else 
            cout << "SNMP++ Error = " << snmp.error_msg( status) << '\n'; 
    } 
}

int main(int argc, char *argv[]) 
{
    mib_walk();
}
