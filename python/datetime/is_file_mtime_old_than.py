
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

if __name__ == "__main__":
    today = datetime.date.today()
    if len(sys.argv) < 3:
        print("usage: {} file days_before_now".format(sys.argv[0]))
        sys.exit(1)

    delta = datetime.timedelta(days=int(sys.argv[2]))
    day = today - delta
    file_path = sys.argv[1]
    if is_file_mtime_old_than(file_path, day):
        print("file: {} mtime is old than {}".format(file_path, day))
    else:
        print("file: {} mtime is new than {}".format(file_path, day))

