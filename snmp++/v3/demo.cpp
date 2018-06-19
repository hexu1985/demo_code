#include <iostream>  
#include "snmp_pp/snmp_pp.h"  

using namespace std;  
using namespace Snmp_pp;

#define SYSDESCR "1.3.6.1.2.1.1.1.0" // Object ID for System Descriptor
  
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

int main(int argc, char *argv[])  
{  
    Snmp::socket_startup();  

    OctetStr securityName("public");
    int securityModel = SNMP_SECURITY_MODEL_USM;
    int securityLevel = SNMP_SECURITY_LEVEL_AUTH_NOPRIV;
//    int securityLevel = SNMP_SECURITY_LEVEL_AUTH_PRIV;
    OctetStr contextName("");
    OctetStr contextEngineID("");

    init_v3(securityName);

    const char *addr_str = "127.0.0.1";
    if (argc == 2) {
        addr_str = argv[1];
    }
    IpAddress ip_addr(addr_str);
  
    UTarget utarget(ip_addr);  
    utarget.set_version(version3);
    utarget.set_security_model(securityModel);
    utarget.set_security_name(securityName);
  
    Vb vb(SYSDESCR);  
    Pdu pdu;  
    pdu += vb;  
    pdu.set_security_level(securityLevel);
    pdu.set_context_name (contextName);
    pdu.set_context_engine_id(contextEngineID);
  
    int status;  
    Snmp snmp(status);  
    if (SNMP_CLASS_SUCCESS != status)  
    {  
        cout << snmp.error_msg(status) << endl;  
        return -1;  
    }  
  
    if ( (status = snmp.get(pdu, utarget)) != SNMP_CLASS_SUCCESS )  
    {  
        cout << snmp.error_msg(status) << endl;  
        return -1;  
    }  
    else  
    {  
        pdu.get_vb(vb, 0);  
        cout << "System Descriptor =" << vb.get_printable_value() << endl;  
    }  
  
    Snmp::socket_cleanup();  
    return 0;  
}  
