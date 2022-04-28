#!/usr/bin/env python3

import sys
import subprocess
import psutil
import pathlib
import datetime
import collections

DataDir = collections.namedtuple('DataDir', 'path carid')

def shell_cmd(cmd, alert_on_failure=True):
    print('SHELL > {}'.format(cmd))
    proc = subprocess.Popen(cmd, shell=True, close_fds=True)
    ret = proc.wait()
    print('ret: {}'.format(ret))

def get_mount_points():
    partitions = psutil.disk_partitions()
    return [ p.mountpoint for p in partitions if p.mountpoint.startswith("/media/") ]

def get_today_date_str():
    today = datetime.datetime.today()
    return today.strftime("%Y%m%d")

def make_dir_p(path):
    print("make_dir_p: {}".format(path))
    try:
        if not path.exists():
            path.mkdir(parents=True)
    except Exception as err:
        print("make_dir_p: {} failed".format(path))

def rsync_dir(from_path, to_path):
    make_dir_p(to_path)
    cmd_str = 'rsync -av "{}/" "{}/"'.format(from_path, to_path)
    shell_cmd(cmd_str)

def rsync_file(from_path, to_path):
    make_dir_p(to_path.parent)
    cmd_str = 'rsync -av "{}" "{}"'.format(from_path, to_path)
    shell_cmd(cmd_str)

def sync_log_data_dir(data_dir, carid):
    date_str = get_today_date_str()
    print("sync_log_data_dir")

    dst_data_dir = pathlib.Path("/gondor")/date_str/carid/"data"
    dst_log_dir = dst_data_dir/"log"

    rsync_dir(data_dir/"log", dst_log_dir)
    for path in data_dir.glob("*"):
        if path.is_file():
            rsync_file(path, dst_data_dir/path.name)

def sync_bag_data_dir(data_dir, carid):
    print("sync_bag_data_dir")
    bag_dir = data_dir/"bag"
    if not bag_dir.is_dir():
        print("{} is not dir".format(bag_dir))
        return

    for record_dir in bag_dir.glob("[0-9]"*8+"-*"):
        date_str = record_dir.name[0:8]
        dst_record_dir = pathlib.Path("/gondor")/date_str/carid/"data"/"bag"/record_dir.name
        rsync_dir(record_dir, dst_record_dir)

def get_src_data_dir_list():
    mount_points = get_mount_points()
    print("mount_points: {}".format(mount_points))
    data_dir_list = []
    for mp in mount_points:
        mp_path = pathlib.Path(mp).resolve()
        for car_dir in mp_path.glob("white-rhino-*"):
            data_dir = car_dir/"data"
            data_dir_list.append(DataDir(path=data_dir, carid=car_dir.name))
    return data_dir_list

def main():
    src_data_dir_list = get_src_data_dir_list()
    for src_data_dir in src_data_dir_list:
        path = src_data_dir.path
        carid = src_data_dir.carid
        print("sync data, path: {}, carid: {}".format(path, carid))
        sync_bag_data_dir(path, carid)
        sync_log_data_dir(path, carid)


if __name__ == "__main__":
    main()
