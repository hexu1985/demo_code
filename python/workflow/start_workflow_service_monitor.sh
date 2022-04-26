#!/bin/bash

function check_workflow_service_alive() 
{
    workflow_service_pid=$(ps aux | grep 'workflow_service/[m]ain.py' | awk '{print $2}')
    if [ -z "$workflow_service_pid" ]
    then
        echo "workflow_service/main.py is not running"
        return 0
    else
        echo "workflow_service/main.py is running"
        return 1
    fi
}


CURRENT_FILE_DIRECTORY=$(cd `dirname $0` && pwd)

echo $CURRENT_FILE_DIRECTORY

while :
do
    check_workflow_service_alive
    if [ "$?" -eq "0" ]
    then
        echo "start workflow_service"
        ${CURRENT_FILE_DIRECTORY}/start_workflow_service.sh
    else
        echo "sleep 30s"
        sleep 30
    fi
done

