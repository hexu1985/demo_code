function get_dst_mount_dir_car_id()
{
    local test_dir=$1
    ls -1d "${test_dir}"/car-* | head -1 | xargs basename
}


car_id=`get_dst_mount_dir_car_id .`
echo "car_id: ${car_id}"
