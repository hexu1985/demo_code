#!/bin/bash

debug=0

# container tag
CONTAINER_TAG=${CONTAINER_TAG:-cont_demo}
((debug)) && echo "CONTAINER_TAG: ${CONTAINER_TAG}"

docker stop ${CONTAINER_TAG}

