#!/usr/bin/env python3

import logging.config
import os
import datetime

def init_logging_config(log_root, log_prefix, log_level=logging.INFO):
    # logging
    LOG_FILE = os.path.join(
        log_root,
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
#                "level": "DEBUG",
                "level": log_level,
                "class": "logging.StreamHandler",
                "formatter": "standard"
            },
            "default": {
#                "level": "INFO",
                "level": log_level,
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

if __name__ == '__main__':
    init_logging_config('.', 'logging_config', logging.INFO)
    LOGGER = logging.getLogger()
    LOGGER.debug("hello debug")
    LOGGER.info("hello info")
    LOGGER.error("hello error")
    LOGGER.warning("hello warning")
