编译snmp++
1)下载snmp包, tar解压
2)cd snmp目录
# ./configure --enable-macaddress --enable-ipxaddress
# make
# ln -s src/.libs lib
# ln -s libsnmp.h include/libsnmp.h

snmpwalk v3
# snmpwalk -v 3 -u public -a SHA -A 12345678 -x AES -X 12345678 -l authNoPriv localhost

snmp参考:
https://wiki.archlinux.org/index.php/snmpd
