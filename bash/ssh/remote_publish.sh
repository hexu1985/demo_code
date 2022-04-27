#!/bin/bash

CURRENT_FILE_DIRECTORY=$(cd `dirname $0` && pwd)

echo $CURRENT_FILE_DIRECTORY

declare -A edge_server_addrs
edge_server_addrs=( [anting]="192.168.199.102" [xinchuan]="192.168.199.102" [xiangcheng]="192.168.199.102" [shushan]="192.168.199.102" [binhaixinqu]="192.168.199.102" )

declare -A edge_server_ports
edge_server_ports=( [anting]="8001" [xinchuan]="8002" [xiangcheng]="8005" [shushan]="8006" [binhaixinqu]="8007" )

for edge_server_name in ${!edge_server_addrs[@]}
do
    dst_ip=${edge_server_addrs[$edge_server_name]}
    dst_port=${edge_server_ports[$edge_server_name]}
    echo "publish to $edge_server_name [${dst_ip}:${dst_port}]"
    rsync -e "ssh -p ${dst_port}" -avzP ${CURRENT_FILE_DIRECTORY} apollo@${dst_ip}:/home/apollo/
    ssh -p ${dst_port} apollo@${dst_ip} "/home/apollo/data_platform/local_publish.sh"
done
