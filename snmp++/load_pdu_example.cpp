#include <iostream>
#include "snmp_pp/vb.h" 
#include "snmp_pp/pdu.h" 

using namespace std;
using namespace Snmp_pp;

#define SYSDESCR "1.3.6.1.2.1.1.1.0" // Object ID for System Descriptor

// example of how to load a Pdu object 
void load_pdu_examples() 
{ 
    Pdu pdu; // create a Pdu object 
    Vb vb; // create a Vb object 
    vb.set_oid( SYSDESCR); // set the oid portion of the Vb to System Descriptor 
    pdu += vb; // loads the Vb to the Pdu 
    
    Pdu my_pdu; // create another Pdu object 
    Vb vbs[5]; // create 5 vbs 
    pdu.set_vblist( vbs,5); // load all 5 to the pdu
}

int main(int argc, char *argv[]) 
{
    load_pdu_examples();
}
