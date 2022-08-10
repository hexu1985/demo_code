import pathlib
import logging
import os

LOGGER = logging.getLogger()

def mkdir_if_not_exists(dir_path):
    path = pathlib.Path(dir_path)
    try:
        path.mkdir(parents=True, exist_ok=True)
    except Exception as e:
        print("mkdir {} failed: {}".format(path, e))
        return False
    return True

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    if mkdir_if_not_exists("./log"):
        LOGGER.info("mkdir ok")
    else:
        LOGGER.info("mkdir failed")
        
