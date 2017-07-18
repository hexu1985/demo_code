#!/opt/local/bin/bash

if (( $# != 1 ))
then
    echo "Usage: $0 num"
    exit 1
fi

array=$(eval echo {1..$1})

for i in ${array[@]}; do echo -n "$RANDOM "; done
