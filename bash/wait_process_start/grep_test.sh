
CURRENT_CMD_NAME=$(basename $0)
pattern=$(echo $1 | sed -e 's/[a-zA-Z]/[&]/')

ps -eaf | grep "${pattern}" | grep -v "${CURRENT_CMD_NAME}" | wc -l
