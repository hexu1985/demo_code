
HIGHER_DIR=$(cd `dirname ${BASH_SOURCE[0]}` && pwd)

echo ${HIGHER_DIR}

VARS_DIR=$(cd ${HIGHER_DIR}/.. && pwd)

. ${VARS_DIR}/vars.sh

echo $(pwd)
