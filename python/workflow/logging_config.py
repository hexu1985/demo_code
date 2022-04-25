#!/usr/bin/env python3

import logging.config
import os
import datetime
import time

def init_logging_config(log_root, log_prefix, log_level=logging.INFO):
    # logging
    LOG_ROOT = log_root
    LOG_FILE = os.path.join(
        LOG_ROOT,
        "%s.log.%s" % 
        (log_prefix, datetime.datetime.now().strftime('%Y%m%d-%H%M%S.%f'))
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
    logging.basicConfig(level=logging.INFO)

if __name__ == '__main__':
    init_logging_config('.', 'logging_config')
    LOGGER = logging.getLogger()
    LOGGER.info("hello info")
    LOGGER.error("hello error")
    LOGGER.warning("hello warning")
