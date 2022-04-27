#!/usr/bin/env python3

import sys
import subprocess
import psutil
import pathlib
import datetime

def shell_cmd(cmd, alert_on_failure=True):
    """Execute shell command and return (ret-code, stdout, stderr)."""
    print('SHELL > {}'.format(cmd))
    proc = subprocess.Popen(cmd, shell=True, close_fds=True,
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ret = proc.wait()
    stdout = proc.stdout.read().decode('utf-8') if proc.stdout else None
    stderr = proc.stderr.read().decode('utf-8') if proc.stderr else None
    if alert_on_failure and stderr and ret != 0:
        sys.stderr.write('{}\n'.format(stderr))
    return (ret, stdout, stderr)

def get_mount_points():
    partitions = psutil.disk_partitions()
    return [ p.mountpoint for p in partitions if p.mountpoint.startswith("/media/") ]

def get_today_date_str():
    today = datetime.datetime.today()
    return today.strftime("%Y%m%d")

def make_dir_p(path):
    print("make_dir_p: {}".format(path))
    if not path.exists():
        path.mkdir(parents=True)

def rsync_dir(from_path, to_path):
    cmd_str = 'rsync -avP "{}/" "{}/"'.format(from_path, to_path)
    shell_cmd(cmd_str)
    pass

def rsync_file(from_path, to_path):
    cmd_str = 'rsync -avP "{}" "{}"'.format(from_path, to_path)
    shell_cmd(cmd_str)
    pass

def sync_bag_dir(from_bag_dir, to_bag_dir, date_str):
    for path in from_bag_dir.glob(date_str+"-*"):
        rsync_dir(path, to_bag_dir/path.name)

def sync_data_dir(data_dir, car_dir_name, date_str):
    print("data_dir: {}, car_dir_name: {}".format(data_dir, car_dir_name))

    # make dst dir if need
    dst_data_dir = pathlib.Path("/gondor")/date_str/car_dir_name/"data"
    make_dir_p(dst_data_dir)

    dst_bag_dir = dst_data_dir/"bag"
    make_dir_p(dst_bag_dir)

    dst_log_dir = dst_data_dir/"log"
    make_dir_p(dst_log_dir)

    sync_bag_dir(data_dir/"bag", dst_bag_dir, date_str)
    rsync_dir(data_dir/"log", dst_log_dir)

    for path in data_dir.glob("*"):
        if path.is_file():
            rsync_file(path, dst_data_dir/path.name)

def main():
    mount_points = get_mount_points()
    print("mount_points: {}".format(mount_points))
    date_str = get_today_date_str()
    print("date_str: {}".format(date_str))
    for mp in mount_points:
        mp_path = pathlib.Path(mp).resolve()
        for car_dir in mp_path.glob("white-rhino-*"):
            data_dir = car_dir/"data"
            if data_dir.is_dir():
                sync_data_dir(data_dir, car_dir.name, date_str)


if __name__ == "__main__":
    main()
