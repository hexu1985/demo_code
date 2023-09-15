#!/bin/bash -

cwd=$(cd `dirname ${BASH_SOURCE[0]}` && pwd)

# image tag
IMAGE_TAG=${IMAGE_TAG:-ubuntu:20.04-demo}
((debug)) && echo "IMAGE_TAG: $IMAGE_TAG"

# dockerfile
DOCKER_FILE=${DOCKER_FILE:-Dockerfile}
((debug)) && echo "DOCKER_FILE: $DOCKER_FILE"

docker build -t ${IMAGE_TAG} -f $cwd/${DOCKER_FILE} .
