#!/usr/bin/env python3

import logging

LOGGER = logging.getLogger()

def print_log():
    LOGGER.info("print info log")
    LOGGER.error("print error log")

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    print_log()
