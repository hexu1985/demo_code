TARGET_FILE=
DEBUG_FILE=

if (( $# >= 1 ))
then
    TARGET_FILE=$1
fi

if [ -z "${TARGET_FILE}" ]
then
    echo "TARGET_FILE is null"
    exit 1
fi

if [ ! -e "${TARGET_FILE}" ]
then
    echo "${TARGET_FILE} is not exist!"
    exit 1
fi

DEBUG_FILE=${TARGET_FILE}.debug

#生成符号文件
objcopy --only-keep-debug ${TARGET_FILE} ${DEBUG_FILE}

#生成发布文件
strip ${TARGET_FILE} -o ${TARGET_FILE}.release
objcopy --add-gnu-debuglink=${DEBUG_FILE} ${TARGET_FILE}.release
mv ${TARGET_FILE}.release ${TARGET_FILE}
