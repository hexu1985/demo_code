#!/usr/bin/env python3

import datetime
import pathlib

def remove_dir_recursive(dir_path):
    try:
        print("remove dir {}".format(dir_path))
        #shutil.rmtree(dir_path)
    except Exception as err:
        print("remove dir {} failed: {}".format(dir_path, err))

if __name__ == "__main__":
    today = datetime.datetime.today()
    datestr = today.strftime("%Y%m%d")
    print("today datestr: {}".format(datestr))

    sevenday_ago = today - datetime.timedelta(days=7)
    datestr = sevenday_ago.strftime("%Y%m%d")
    print("7day ago datestr: {}".format(datestr))

    date_end = int(datestr)

    root_path = pathlib.Path("/gondor").resolve()
    for subdir in root_path.glob('[0-9]'*8):    # only process name yyyymmdd dir
        date_int = int(subdir.name)
        if date_int <= date_end:
            remove_dir_recursive(subdir)




