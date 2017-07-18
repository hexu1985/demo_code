#!/bin/sh
# for bj.efs.sina.com.cn

# argc check
if (( $# != 2 ))
then
  echo "usage: wget_esf_sina.sh url outdir"
  exit 1
fi

INDEX_URL=$1
OUT_DIR=$2

# check url
if [[ ! "${INDEX_URL}" == *esf.sina.com.cn* ]]
then
  echo "only support url of esf.sina.com.cn"
  exit 2
fi

# test if out_dir exists
# if need to mkdir
if [ ! -e "${OUT_DIR}" ]
then
  echo "${OUT_DIR} not exists. will create..."
  if ! mkdir ${OUT_DIR}
  then
    echo "mkdir ${OUT_DIR} fail."
    exit 3
  fi
fi

if [ ! -d "${OUT_DIR}" ]
then
  echo "${OUT_DIR} not directory."
  exit 3
fi

# get index url
if ! wget -O ${OUT_DIR}/index.html ${INDEX_URL}
then
  echo "wget ${INDEX_URL} error"
  exit 4
fi

# get max page number line
MAX_PAGE_LINE=$(grep '<span class="all">.*</span>' ${OUT_DIR}/index.html)
echo ${MAX_PAGE_LINE}

str_len=$(echo ${MAX_PAGE_LINE} | wc -c)
if (( str_len == 0 ))
then
  echo "no match total pages"
  exit 5
fi

# get max page number
MAX_PAGE=$(echo ${MAX_PAGE_LINE} | sed 's/.*¹²\(.*\)Ò³.*/\1/g')
echo ${MAX_PAGE}

str_len=$(echo ${MAX_PAGE} | wc -c)
if (( str_len == 0 ))
then
  echo "no total page number"
  exit 5
fi

URL_PREFIX=$(echo ${INDEX_URL} | sed 's!\(.*\)/!\1!g')
echo ${URL_PREFIX}

page_index=1
while (( page_index <= MAX_PAGE ))
do
  wget -O ${OUT_DIR}/N${page_index}.html "${URL_PREFIX}-n${page_index}/"
  (( page_index++  ))
done
