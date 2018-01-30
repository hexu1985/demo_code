#include <iostream>
#include "snmp_pp/snmp_pp.h"  

using namespace std;
using namespace Snmp_pp;

#define COLDSTART	"1.3.6.1.6.3.1.1.4.3.0.1"
#define SYSLOCATION	"1.3.6.1.2.1.1.6.0"

void send_trap() 
{ 
    int status; // return status 
    CTarget target( (IpAddress) "127.0.0.1"); // SNMP++ v1 target
    Pdu pdu; // SNMP++ PDU 
    Vb vb;
    
    //-------[ Construct a SNMP++ SNMP Object ]--------------------------------------- 
    Snmp snmp( status); // Create a SNMP++ session 
    if ( status != SNMP_CLASS_SUCCESS) { // check creation status 
        cout << snmp.error_msg( status) << '\n'; // if fail, print error string 
        return; 
    } 
    
    std::cout << "Send a TRAP to: " << target.get_address().get_printable() << std::endl;

    Oid notify_oid(COLDSTART);
    if ( ! notify_oid.valid() ) {
        std::cout << "Notify oid constructor failed for:" << COLDSTART << std::endl;
        return; 
    }

    pdu.set_notify_id(notify_oid);

    // Use a simple payload
    vb.set_oid(SYSLOCATION);
    vb.set_value("hello");
    pdu += vb;
    status = snmp.trap( pdu, target); 
    cout << " Trap Send Status = " << snmp.error_msg( status) << '\n'; 
}

int main(int argc, char *argv[]) 
{
    send_trap();
}
