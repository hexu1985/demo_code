#!/usr/bin/env bash

function download() {
    local outfile=$1
    local url=$2
    echo "downloading $url and save to $outfile"
    wget -O $outfile $url
    echo "download $url and save to $outfile ok"
}
#wget https://github.com/hexu1985/design_pattern/archive/master.zip

declare -A url_map
url_map["design_pattern.zip"]="https://github.com/hexu1985/design_pattern/archive/master.zip"
url_map["demo.zip"]="https://github.com/hexu1985/demo/archive/master.zip"
url_map["doc.zip"]="https://github.com/hexu1985/doc/archive/master.zip"
url_map["algo_code.zip"]="https://github.com/hexu1985/algo_code/archive/master.zip"
url_map["unp_code.zip"]="https://github.com/hexu1985/unp_code/archive/master.zip"
url_map["book_code.zip"]="https://github.com/hexu1985/book_code/archive/master.zip"
url_map["math_note.zip"]="https://github.com/hexu1985/math_note/archive/master.zip"
url_map["computer_note.zip"]="https://github.com/hexu1985/computer_note/archive/master.zip"
url_map["graph_qt.zip"]="https://github.com/hexu1985/graph_qt/archive/master.zip"
url_map["util_code.zip"]="https://github.com/hexu1985/util_code/archive/master.zip"
url_map["lib_code.zip"]="https://github.com/hexu1985/lib_code/archive/master.zip"
url_map["stunserver.zip"]="https://github.com/hexu1985/stunserver/archive/master.zip"
url_map["sniffer.zip"]="https://github.com/hexu1985/sniffer/archive/master.zip"
url_map["nginx_load_balance.zip"]="https://github.com/hexu1985/nginx_load_balance/archive/master.zip"
url_map["cpp_code.zip"]="https://github.com/hexu1985/cpp_code/archive/master.zip"
url_map["unix_code.zip"]="https://github.com/hexu1985/unix_code/archive/master.zip"

pwd
dir_name=$(dirname $0)
cd $dir_name
pwd

outdir="git_""$(date +"%y%m%d")"
rm -rf $outdir
mkdir $outdir

olddir=$(pwd)
cd $outdir

for key in ${!url_map[*]}
do
    download $key ${url_map[$key]}
done

cd $olddir
tar czvf ./${outdir}.tar.gz ${outdir}
