#!/bin/bash

CURRENT_FILE_DIRECTORY=$(cd `dirname $0` && pwd)

killall -9 start_workflow_service_monitor.sh
${CURRENT_FILE_DIRECTORY}/stop_workflow_service.sh
