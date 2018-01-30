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
  Vb nextVb;
  int pdu_error;
  GenAddress addr;

  target.get_address(addr);
  UdpAddress from(addr);

  std::cout << "reason: " << reason << std::endl
       << "msg: " << session->error_msg(reason) << std::endl
       << "from: " << from.get_printable() << std::endl;

  pdu_error = pdu.get_error_status();
  if (pdu_error){
    std::cout << "Response contains error: " 
	 << session->error_msg(pdu_error)<< std::endl;
  }
  Oid id;
  pdu.get_notify_id(id);
  std::cout << "ID:  " << id.get_printable() << std::endl;
  std::cout << "Type:" << pdu.get_type() << std::endl;

  for (int i=0; i<pdu.get_vb_count(); i++)
  {
    pdu.get_vb(nextVb, i);

    std::cout << "Oid: " << nextVb.get_printable_oid() << std::endl
	 << "Val: " <<  nextVb.get_printable_value() << std::endl;
  }
  if (pdu.get_type() == sNMP_PDU_INFORM) {
      std::cout << "pdu type: " << pdu.get_type() << std::endl;
      std::cout << "sending response to inform: " << std::endl;
      nextVb.set_value("This is the response.");
      pdu.set_vb(nextVb, 0);
      session->response(pdu, target);
  }
  std::cout << std::endl;
}

//---------------[ trap receive register ]--------------------------------------------------------------------- 

Snmp *trap_register() 
{ 
    //----------------[ instantiate an Snmp object, delete when no longer receiving traps ]------------ 
    int status; 
    Snmp *snmp = new Snmp( status); 
    if (( snmp == NULL) || ( status != SNMP_CLASS_SUCCESS)) {
        cout << "Error constructing Snmp Object\n"; 
        return NULL;
    } else { 
        //-------[ set up two empty collections, empty denotes receive all ]------------------------------- 
        TargetCollection targets; 
        OidCollection trapids; 

        //------[ invoke the regsiter ]---------------------------------------------------------------------------- 
        if (( status = snmp->notify_register( trapids, targets, & my_trap_callback)) != SNMP_CLASS_SUCCESS) {
            cout << " Snmp Trap Register Error " << snmp->error_msg( status) << '\n'; 
            return NULL;
        }
    } 

    return snmp;
}

int main(int argc, char *argv[])
{
    Snmp *snmp = trap_register();
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
