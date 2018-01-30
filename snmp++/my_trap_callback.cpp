#include <stdio.h>
#include "snmp_pp/snmp_pp.h"

using namespace std;
using namespace Snmp_pp;

//-----------------[ trap callback function definition ]------------------------------------------------------------------- 
void my_trap_callback ( int reason, // reason 
        Snmp* session, // session handle 
        Pdu & pdu, // trap pdu 
        SnmpTarget &target, // source of the trap 
        void * cbd) // optional callback data 
{
    GenAddress address; 
    OctetStr get_community, set_community;
    unsigned long timeout; 
    int retry; 
    unsigned char version;
    
    if ( reason == SNMP_CLASS_NOTIFICATION) { 
        dynamic_cast<CTarget &>(target).resolve_to_C( get_community, // get community 
                set_community, // set community 
                address, // address object 
                timeout, // timeout 
                retry, // retry 
                version);   // version
        Oid trapid;
        pdu.get_notify_id(trapid);
        cout << "Trap Received from " << address.get_printable() << "Trap Id = " << trapid.get_printable() << '\n'; 
    }
        else cout << "Trap Receive Error = " << session->error_msg( reason) << '\n';
}

//---------------[ trap receive register ]--------------------------------------------------------------------- 
Snmp *snmp = 0; // dynamic Snmp object

void trap_register() 
{ 
    //----------------[ instantiate an Snmp object, delete when no longer receiving traps ]------------ 
    int status; 
    snmp = new Snmp( status); 
    if (( snmp == NULL) || ( status != SNMP_CLASS_SUCCESS)) {
        cout << "Error constructing Snmp Object\n"; 
    } else { 
        //-------[ set up two empty collections, empty denotes receive all ]------------------------------- 
        TargetCollection targets; 
        OidCollection trapids; 

        //------[ invoke the regsiter ]---------------------------------------------------------------------------- 
        if (( status = snmp->notify_register( trapids, targets, & my_trap_callback)) != SNMP_CLASS_SUCCESS) {
            cout << " Snmp Trap Register Error " << snmp->error_msg( status) << '\n'; 
        }
    } 
}

int main(int argc, char *argv[])
{
    trap_register();
    if (snmp == NULL)
        return 0;

    int trap_port = 162;
    std::cout << "Trying to register for traps on port " << trap_port << "." << std::endl;
    snmp->notify_set_listen_port(trap_port);

    snmp->start_poll_thread(1000);

    std::cout << "press return to stop\n";
    getc(stdin);

    snmp->stop_poll_thread();
}
