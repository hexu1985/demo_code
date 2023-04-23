import pathlib
import datetime

def create_datetime(ts):
    return datetime.datetime.fromtimestamp(ts)

current_path = pathlib.Path(__file__)
print("file: {}".format(current_path))
print("stat: {}".format(current_path.stat()))
stat = current_path.stat()
print("atime: {}".format(create_datetime(stat.st_atime)))
print("mtime: {}".format(create_datetime(stat.st_mtime)))
print("ctime: {}".format(create_datetime(stat.st_ctime)))

print("atime: {}".format(stat.st_atime))
print("mtime: {}".format(stat.st_mtime))
print("ctime: {}".format(stat.st_ctime))
