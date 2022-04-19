import logging
import logging_config
import a


logging.basicConfig(level=logging.INFO)
LOGGER = logging.getLogger()
LOGGER.info("hello info")
LOGGER.error("hello error")
LOGGER.warning("hello warning")
a.print_log()
