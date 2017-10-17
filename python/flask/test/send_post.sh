#!/usr/bin/env bash

HTTP_HEADER="Content-type: application/json"
HTTP_PAYLOAD="hello"
URL="http://localhost/"

while getopts f:hu: options
do
    case $options in
        f) HTTP_PAYLOAD=$(cat ${OPTARG});;
        u) URL=${OPTARG};;
        h|\?) echo "usage: $0 [-f http_data_file] [-d url]"; exit 1;;
    esac
done

curl -i -X POST -H "${HTTP_HEADER}" -d "${HTTP_PAYLOAD}" ${URL}
