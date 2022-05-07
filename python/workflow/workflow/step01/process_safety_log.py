#!/usr/bin/env python3

import os
import sys
import pathlib
import collections
import subprocess

GONDOR_ROOT_PATH = "/gondor"
OUTPUT_ROOT_PATH = "/gondor/upload"
LATC_FILE_PREFIX = "latency"

DataLogDir = collections.namedtuple('DataLogDir', 'path date carid')

def shell_cmd(cmd):
    print('SHELL > {}'.format(cmd))
    proc = subprocess.Popen(cmd, shell=True, close_fds=True)
    ret = proc.wait()
    print('ret: {}'.format(ret))

def get_current_file_path():
    current_file_path=os.path.dirname(sys.argv[0])
    if not current_file_path:
        current_file_path = os.getcwd()
    current_file_path = pathlib.Path(current_file_path).resolve()
    return str(current_file_path)

def get_gondor_data_log_dir_list():
    data_log_dir_list = []
    root_path = pathlib.Path(GONDOR_ROOT_PATH).resolve() 
    for date_path in root_path.glob("[0-9]"*8):
        for car_dir in date_path.glob("white-rhino-*"):
            data_log_dir = car_dir/"data"/"log"
            if data_log_dir.exists() and data_log_dir.is_dir(): 
                data_log_dir_list.append(DataLogDir(path=data_log_dir, date=date_path.name, carid=car_dir.name))
    return data_log_dir_list

def get_safety_log_date(safety_log_file_name):
    # file_name like 'safety.log.info.20220505-091418.11987'
    front_part = safety_log_file_name.split('-')[0]
    date_str = front_part.split('.')[3]
    return date_str

def get_safety_log_datetime(safety_log_file_name):
    # file_name like 'safety.log.info.20220505-091418.11987'
    front_part = safety_log_file_name.split('-')[0]
    timestamp = safety_log_file_name.split('-')[1]
    date_str = front_part.split('.')[3]
    return date_str+'-'+timestamp 

def gen_latc_csv_file_path(safety_log_file_name, dir_path):
    file_name = LATC_FILE_PREFIX+"."+get_safety_log_datetime(safety_log_file_name)+".csv"
    return dir_path/file_name

def gen_latc_png_file_path(safety_log_file_name, dir_path):
    file_name = LATC_FILE_PREFIX+"."+get_safety_log_datetime(safety_log_file_name)+".png"
    return dir_path/file_name

def get_output_dir_path(date_str, carid):
    output_dir_path = pathlib.Path(OUTPUT_ROOT_PATH)/date_str/carid
    try:
        output_dir_path.mkdir(parents=True, exist_ok=True)
    except Exception as e:
        print("mkdir {} failed".format(output_dir_path))

    return output_dir_path

def process_safety_log(safety_log_file, carid):
    safety_log_file_name = safety_log_file.name
    date_str = get_safety_log_date(safety_log_file_name)
    print("process {} of {} {}".format(safety_log_file, date_str, carid))
    output_dir_path = get_output_dir_path(date_str, carid)
    current_file_path = get_current_file_path()
    print("current_file_path: {}".format(current_file_path))
    latc_csv_file = gen_latc_csv_file_path(safety_log_file_name, output_dir_path)
    latc_png_file = gen_latc_png_file_path(safety_log_file_name, output_dir_path)
    print("latc_csv_file: {}".format(latc_csv_file))
    print("latc_png_file: {}".format(latc_png_file))
    if latc_png_file.exists():
        print("{} already process".format(safety_log_file))
        return
    cmd_str = "bash {}/latc/analyze_latency.sh {} {} {}".format(current_file_path, safety_log_file, latc_csv_file, latc_png_file)
    shell_cmd(cmd_str) 


if __name__ == "__main__":
    data_log_dir_list = get_gondor_data_log_dir_list()
    print("data_log_dir_list: {}\n".format(data_log_dir_list))
    for data_log_dir in data_log_dir_list:
        log_dir = data_log_dir.path
        carid = data_log_dir.carid
        for safety_log_file in log_dir.glob("safety.log.info."+"[0-9]"*8+"-*"):
            process_safety_log(safety_log_file, carid)
            print()
