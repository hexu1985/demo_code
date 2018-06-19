#include <iostream>
#include "snmp_pp/snmp_pp.h"  

using namespace std;
using namespace Snmp_pp;

v3MP *init_v3(const OctetStr &securityName)
{
    OctetStr privPassword("12345678");
    OctetStr authPassword("12345678");
    long authProtocol = SNMP_AUTHPROTOCOL_HMACSHA;
    long privProtocol = SNMP_PRIVPROTOCOL_AES128;
    unsigned int snmpEngineBoots = 0;

    const char *engineId = "snmpNext";

    int construct_status;
    v3MP *v3_MP = new v3MP(engineId, snmpEngineBoots, construct_status);
    if (construct_status != SNMPv3_MP_OK)
    {
        std::cout << "Error initializing v3MP: " << construct_status << std::endl;
        exit(1);
    }

    USM *usm = v3_MP->get_usm();
    usm->add_usm_user(securityName,
            authProtocol, privProtocol,
            authPassword, privPassword);
    return v3_MP;
}

void mib_bulk() 
{
    OctetStr securityName("public");
    int securityModel = SNMP_SECURITY_MODEL_USM;
    int securityLevel = SNMP_SECURITY_LEVEL_AUTH_PRIV;
    OctetStr contextName("");
    OctetStr contextEngineID("");

    init_v3(securityName);

    int status; // return status 
    UTarget utarget( (IpAddress) "127.0.0.1"); // SNMP++ v3 target 
    utarget.set_version(version3);
    utarget.set_security_model(securityModel);
    utarget.set_security_name(securityName);
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
    pdu.set_security_level(securityLevel);
    pdu.set_context_name (contextName);
    pdu.set_context_engine_id(contextEngineID);
    
    status = SNMP_CLASS_SUCCESS; 
    int non_reps = 0;
    int max_reps = 40;
    while ( status == SNMP_CLASS_SUCCESS) { 
        if ( (status = snmp.get_bulk(pdu,utarget,non_reps,max_reps)) == SNMP_CLASS_SUCCESS) { 
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
