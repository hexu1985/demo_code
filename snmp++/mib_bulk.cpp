#include <iostream>
#include "snmp_pp/snmp_pp.h"  

using namespace std;
using namespace Snmp_pp;

void mib_bulk() 
{
    int status; // return status 
    CTarget target( (IpAddress) "127.0.0.1"); // SNMP++ v2c target 
    target.set_version(version2c);
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
    int non_reps = 0;
    int max_reps = 40;
    while ( status == SNMP_CLASS_SUCCESS) { 
        if ( (status = snmp.get_bulk(pdu,target,non_reps,max_reps)) == SNMP_CLASS_SUCCESS) { 
            cout << "---------------------------------------------------------------------" << '\n';
            cout << "vb.count: " << pdu.get_vb_count() << '\n';
            for (int z=0;z<pdu.get_vb_count();z++) {
                pdu.get_vb(vb,z);   // extract the vb 
                std::cout << "Mib Object = " << vb.get_printable_oid() << "\n";
                if (vb.get_syntax() != sNMP_SYNTAX_ENDOFMIBVIEW) {
                    std::cout << "Mib Value = " << vb.get_printable_value() << "\n\n";
                } else {
                    std::cout << "End of MIB view.\n\n";
                    status = SNMP_CLASS_ERROR;
                    break;
                }
            }
            cout << "---------------------------------------------------------------------" << '\n';
            pdu.clear();
            pdu += vb;
        } else 
            cout << "SNMP++ Error = " << snmp.error_msg( status) << '\n'; 
    } 
}

int main(int argc, char *argv[]) 
{
    mib_bulk();
}
