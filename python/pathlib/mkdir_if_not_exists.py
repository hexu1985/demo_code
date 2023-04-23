import pathlib
import logging
import os

LOGGER = logging.getLogger()

def mkdir_if_not_exists(dir_path):
    path = pathlib.Path(dir_path)
    if path.exists():
        if not path.is_dir():
            LOGGER.error('path "{}" already exist but not dir'.format(path))
            return False
        elif not os.access(dir_path, os.W_OK):
            LOGGER.error('path "{}" already exist but not write permission'.format(path))
            return False
        else:
            return True
    else:
        path.mkdir(parents=True, exist_ok=True)
        return True


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    if mkdir_if_not_exists("./log/abc"):
        LOGGER.info("mkdir ok")
    else:
        LOGGER.info("mkdir failed")
        
