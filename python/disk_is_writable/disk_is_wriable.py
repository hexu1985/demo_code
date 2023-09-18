
import traceback
import logging
import datetime
import sys

LOGGER = logging.getLogger()

def disk_is_writable(disk_path):
    test_file_path=disk_path+"/record_bag_test_writable.txt"
    try:
        f=open(test_file_path, 'w')
        f.write("test writable at {}\n".format(datetime.datetime.now().strftime('%Y%m%d-%H%M%S')))
        f.close()
        LOGGER.info("disk {} is writable".format(disk_path))
        return True
    except OSError as e:
        LOGGER.error("disk {} is not writable: {}".format(disk_path, e))
        return False
    except:
        LOGGER.error("disk {} is not writable: {}".format(disk_path, traceback.format_exc(limit=1)))
        return False


if __name__ == "__main__":
    test_path = "/home/abc"
    if len(sys.argv) > 1:
        test_path = sys.argv[1]
    ret = disk_is_writable(test_path)
    print("{} is wriable? {}".format(test_path, ret))
