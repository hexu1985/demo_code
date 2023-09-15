#!/bin/bash

debug=0

# current file dir
CURRENT_FILE_DIR=$(cd `dirname ${BASH_SOURCE[0]}` && pwd)
((debug)) && echo "CURRENT_FILE_DIR: $CURRENT_FILE_DIR"

# image tag
IMAGE_TAG=${IMAGE_TAG:-ubuntu:20.04-demo}
((debug)) && echo "IMAGE_TAG: $IMAGE_TAG"

# container tag
CONTAINER_TAG=${CONTAINER_TAG:-cont_demo}
((debug)) && echo "CONTAINER_TAG: $CONTAINER_TAG"

# mount src dir
MOUNT_SRC_DIR=${MOUNT_SRC_DIR:-/home/hexu}
((debug)) && echo "MOUNT_SRC_DIR: $MOUNT_SRC_DIR"

# mount dst dir
MOUNT_DST_DIR=${MOUNT_DST_DIR:-/home/hexu}
((debug)) && echo "MOUNT_DST_DIR: $MOUNT_DST_DIR"


docker run -itd \
    --name ${CONTAINER_TAG} \
    --mount type=bind,src=${MOUNT_SRC_DIR},dst=${MOUNT_DST_DIR} \
    --mount type=bind,src=/tmp/corefile,dst=/home/hexu/corefile \
    --ulimit core=-1 \
    --rm ${IMAGE_TAG}

