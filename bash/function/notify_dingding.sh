function notify_rsync_success()
{
    local mount_dir=$1
    local car_id=$2
    local list_file=$3
    local msg_file=`mktemp -t dingding.$$.XXXXXXXX`
    echo "sync imgs to ${mount_dir}/imgs success." > ${msg_file}
    echo "car id maybe: ${car_id}" >> ${msg_file}
    echo "file list is:" >> ${msg_file}
    cat ${list_file} >> ${msg_file}
    date >> ${msg_file}
    python3 ${current_file_path}/sync_imgs_to_car/notify_dingding_from_file.py ${msg_file}
    rm ${msg_file}
}

function notify_rsync_failed()
{   
    local mount_dir=$1
    local car_id=$2
    local msg_file=`mktemp -t dingding.$$.XXXXXXXX`
    echo "sync imgs to ${mount_dir}/imgs failed." > ${msg_file}
    echo "car id maybe: ${car_id}" >> ${msg_file}
    date >> ${msg_file}
    python3 ${current_file_path}/sync_imgs_to_car/notify_dingding_from_file.py ${msg_file}
    rm ${msg_file}
}

current_file_path=$(cd `dirname $0`; pwd)

notify_rsync_success "/run/user/1000" "white-rhino-013" file_list.txt

notify_rsync_failed "/run/user/123" "white-rhino-012"
