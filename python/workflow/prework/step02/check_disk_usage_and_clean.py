#!/usr/bin/env python3

import datetime
import pathlib
import shutil
import psutil
import sys

FREE_BYTES_LIMIT = 1024*1024*1024*1024  # 1TB free
ROOT_PATH = "/gondor"

def remove_dir_recursive(dir_path):
    try:
        print("remove dir {}".format(dir_path))
        shutil.rmtree(dir_path)
    except Exception as err:
        print("remove dir {} failed: {}".format(dir_path, err))

def get_disk_free_bytes(path):
    du = psutil.disk_usage(path)
    return du.free

def is_gondor_space_enough():
    free_bytes = get_disk_free_bytes(ROOT_PATH)
    print('{} free space: {:.3f}GB'.format(ROOT_PATH, free_bytes/(1024*1024*1024)))
    return free_bytes >= FREE_BYTES_LIMIT

def delete_data_day_before(nday):
    today = datetime.datetime.today()
    datestr = today.strftime("%Y%m%d")
    print("today datestr: {}".format(datestr))

    nday_ago = today - datetime.timedelta(days=nday)
    datestr = nday_ago.strftime("%Y%m%d")
    print("{} day ago datestr: {}".format(nday, datestr))

    date_end = int(datestr)

    root_path = pathlib.Path(ROOT_PATH).resolve()
    for subdir in root_path.glob('[0-9]'*8):    # only process name yyyymmdd dir
        date_int = int(subdir.name)
        if date_int <= date_end:
            remove_dir_recursive(subdir)

if __name__ == "__main__":
    if is_gondor_space_enough():
        sys.exit(0)

    for i in [7, 6, 5, 4]:
        if not is_gondor_space_enough():
            print("gondor space is not enough: delete data {} day before".format(i))
            delete_data_day_before(i)
