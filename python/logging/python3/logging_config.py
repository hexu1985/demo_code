#!/usr/bin/env python3

import logging.config
import datetime
import time
import pathlib

def init_logging_config(log_root, log_prefix):
    # logging
    LOG_ROOT = pathlib.Path(log_root)
    LOG_ROOT.mkdir(parents=True, exist_ok=True)
    LOG_FILE = LOG_ROOT/"{}.log.{}".format(log_prefix, datetime.datetime.now().strftime('%Y%m%d-%H%M%S.%f'))
    LOGGING = {
        "version": 1,
        "disable_existing_loggers": False,
        "formatters": {
            "standard": {
                "format":
                    ("[%(levelname)s][%(asctime)s][%(threadName)s:%(thread)d]"
                     "[%(filename)s:%(lineno)d] %(message)s")
            },
        },
        "handlers": {
            "console": {
                "level": "DEBUG",
                "class": "logging.StreamHandler",
                "formatter": "standard"
            },
            "default": {
                "level": "INFO",
                "class": "logging.handlers.TimedRotatingFileHandler",
                "filename": LOG_FILE,
                "when": 'D',
                "interval": 1,
                "backupCount": 7,
                "formatter": "standard",
                "encoding": "utf-8",
            },
        },
        "loggers": {
            "": {
                "handlers": ["console", "default"],
                "level": "DEBUG",
                "propagate": True,
            },
        },
    }
    
    logging.config.dictConfig(LOGGING)

if __name__ == '__main__':
    init_logging_config('.', 'logging_config')
    LOGGER = logging.getLogger()
    LOGGER.info("hello info")
    LOGGER.error("hello error")
    LOGGER.warning("hello warning")
