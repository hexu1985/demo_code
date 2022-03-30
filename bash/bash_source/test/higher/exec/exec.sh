
EXEC_DIR=$(cd `dirname ${BASH_SOURCE[0]}` && pwd)
echo "exec path: ${EXEC_DIR}"

HIGHER_DIR=$(cd ${EXEC_DIR}/.. && pwd)

. ${HIGHER_DIR}/higher.sh

echo "hello exec.sh"
