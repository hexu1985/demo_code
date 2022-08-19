#!/usr/bin/env python3

import logging

LOGGER = logging.getLogger()

def print_log():
    LOGGER.info("print info log")
    LOGGER.error("print error log")
    LOGGER.warning("print warning log")

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format=("[%(levelname)s][%(asctime)s][%(threadName)s:%(thread)d]"
                     "[%(filename)s:%(lineno)d] %(message)s"))
    print_log()
