#!/bin/bash

CURRENT_FILE_DIRECTORY=$(cd `dirname $0` && pwd)

echo $CURRENT_FILE_DIRECTORY

echo "install 3rd dependencies"
SUB_PROCESS=$(cd ${CURRENT_FILE_DIRECTORY}/edge_server/workflow_service/ && ./install_deps.sh)
echo ${SUB_PROCESS}

echo "build uevent_monitor"
SUB_PROCESS=$(cd ${CURRENT_FILE_DIRECTORY}/edge_server/workflow_service/ && make)
echo ${SUB_PROCESS}

echo "install files"
sudo rsync -avp ${CURRENT_FILE_DIRECTORY} /opt
unlink $HOME/workflow
ln -s /opt/data_platform/edge_server/workflow_service/workflow $HOME/workflow

echo "restart service"
sudo cp /opt/data_platform/edge_server/workflow_service/workflow.service /lib/systemd/system/
sudo systemctl daemon-reload
sudo systemctl stop workflow.service
sudo systemctl start workflow.service
sudo systemctl enable workflow.service
sleep 3
ps -eaf | grep '[w]orkflow_service'

