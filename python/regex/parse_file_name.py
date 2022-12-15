
import re
import datetime

def get_time_from_file_name(file_name):
    print("file_name: {}".format(file_name))
    pattern = r'safety_collision\.log\.info\.(\d{8}-\d{6})\..*'
    m = re.match(pattern, file_name) 
    if m is None:
        print("not match")
        return 0
    date_str = str(m.group(1))
    print("date_str: {}".format(date_str))
    date = datetime.datetime.strptime(date_str, "%Y%m%d-%H%M%S")
    return date.timestamp()


if __name__ == "__main__":
    print(get_time_from_file_name("safety_collision.log.info.20221213-093236.17144"))
