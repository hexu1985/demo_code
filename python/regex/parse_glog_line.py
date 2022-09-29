
import re
import datetime

def get_time_from_line(line):
    front14char = line[0:14]
    print("front14char: {}".format(front14char))
    pattern = r'[IWEF]\d{4} \d{2}:\d{2}:\d{2}' 
    if re.match(pattern, front14char) is None:
        print("not match")
        return None
    timestr = line[6:14]
    print("timestr: {}".format(timestr))
    hour = int(line[6:8])
    minute = int(line[9:11])
    second = int(line[12:14])
    if 0 <= hour < 24 and 0 <= minute < 60 and 0 <= second < 60:
        return datetime.time(hour, minute, second)
    else:
        print("invalid time")
        return None



if __name__ == "__main__":
    line = 'W0912 13:40:20.978339  7603 scheduler_factory.cc:64]  No sched conf found, use default conf.'
    print(get_time_from_line(line))
    line = 'All arguments are optional. tzinfo may be None, or an instance of'
    print(get_time_from_line(line))
    line = 'W0912 ss:40:20.978339  7603 scheduler_factory.cc:64]  No sched conf found, use default conf.'
    print(get_time_from_line(line))
    line = 'W0912 77:40:20.978339  7603 scheduler_factory.cc:64]  No sched conf found, use default conf.'
    print(get_time_from_line(line))
