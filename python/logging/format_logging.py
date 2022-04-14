#!/usr/bin/env python3

import logging.config
import os
import datetime

import a

# logging
LOG_ROOT = "."
LOG_FILE = os.path.join(
    LOG_ROOT,
    "test.log.%s" %
    datetime.datetime.now().strftime('%Y%m%d-%H%M%S.%f')
)
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
            "class": "logging.handlers.RotatingFileHandler",
            "filename": LOG_FILE,
            "maxBytes": 1024 * 1024 * 30,
            "backupCount": 3,
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
LOGGER = logging.getLogger()

if __name__ == '__main__':
    LOGGER.info("hello info")
    LOGGER.error("hello error")
    a.print_log()
