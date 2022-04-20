import logging
import logging_config
import a


logging_config.init_logging_config('.', 'logging_config')
LOGGER = logging.getLogger()
LOGGER.info("hello info")
LOGGER.error("hello error")
LOGGER.warning("hello warning")
a.print_log()
