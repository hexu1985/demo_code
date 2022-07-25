#!/usr/bin/env python3

def car_id_str_to_int(car_id):
    prefix = "white-rhino-"
    if car_id.startswith(prefix):
        return int(car_id[len(prefix):])
    return 0

if __name__ == "__main__":
    print("white-rhino-013, car_id={}".format(car_id_str_to_int("white-rhino-013")))
    print("white-rhino-003, car_id={}".format(car_id_str_to_int("white-rhino-003")))
    print("003, car_id={}".format(car_id_str_to_int("003")))
