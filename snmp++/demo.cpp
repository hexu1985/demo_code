#include <iostream>  
#include "snmp_pp/snmp_pp.h"  

using namespace std;  
using namespace Snmp_pp;

#define SYSDESCR "1.3.6.1.2.1.1.1.0" // Object ID for System Descriptor
  
int main(int argc, char *argv[])  
{  
    Snmp::socket_startup();  

    const char *addr_str = "127.0.0.1";
    if (argc == 2) {
        addr_str = argv[1];
    }
    IpAddress ip_addr(addr_str);
  
    CTarget target(ip_addr);  
    target.set_version(version1);  
  
    Vb vb(SYSDESCR);  
    Pdu pdu;  
    pdu += vb;  
  
    int status;  
    Snmp snmp(status);  
    if (SNMP_CLASS_SUCCESS != status)  
    {  
        cout << snmp.error_msg(status) << endl;  
        return -1;  
    }  
  
    cout << "目的IP：" << target.get_address().get_printable() << " 版本号：" << target.get_version() << endl;  
    cout << "read共同体：" << target.get_readcommunity() << "  write共同体：" << target.get_writecommunity() << endl;  
  
    if ( (status = snmp.get(pdu, target)) != SNMP_CLASS_SUCCESS )  
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
