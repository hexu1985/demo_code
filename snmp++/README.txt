编译snmp++
1)下载snmp包, tar解压
2)cd snmp目录
# ./configure --enable-macaddress --enable-ipxaddress
# make
# ln -s src/.libs lib
# ln -s libsnmp.h include/libsnmp.h
