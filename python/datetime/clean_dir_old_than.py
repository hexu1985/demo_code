import datetime
import os
import sys

def is_file_mtime_old_than(file_path, day):
    mtime_day = datetime.date.fromtimestamp(os.path.getmtime(file_path))
    print("file: {}, mtime date: {}".format(file_path, mtime_day))
    if mtime_day < day:
        return True
    else:
        return False

def delete_file(file_path):
    try:
        os.remove(file_path)
        print("remove file {}".format(file_path))
    except Exception as err:
        print("remove file {} failed: {}".format(file_path, err))

def delete_regular_file_old_than(file_path, date_day):
    if not os.path.isfile(file_path):
        return

    if os.path.islink(file_path):
        return

    if not is_file_mtime_old_than(file_path, today):
        return

    delete_file(file_path)

def clean_dir_old_than(dir_path, date_day):
    if not os.path.isdir(dir_path):
        return

    for f_name in os.listdir(dir_path):
        f_path = os.path.join(dir_path, f_name)
        delete_regular_file_old_than(f_path, date_day)

if __name__ == "__main__":
    today = datetime.date.today()
    if len(sys.argv) < 3:
        print("usage: {} file days_before_now".format(sys.argv[0]))
        sys.exit(1)

    delta = datetime.timedelta(days=int(sys.argv[2]))
    day = today - delta
    dir_path = sys.argv[1]
    clean_dir_old_than(dir_path, day)
