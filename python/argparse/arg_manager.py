import logging
import argparse

LOGGER = logging.getLogger()

class ArgManager(object):
    """Arguments manager."""

    def __init__(self):
        self.parser = argparse.ArgumentParser(
            description="clean apollo record data.")
        self.parser.add_argument('--bag_dir_path', default=None, action="store",
                                 dest="BAG_DIR_PATH", type=str,
                                 help='bag dir path'
                                 'example: --bag_dir_path /media/apollo/xxx/white-rhino-013/data/bag')
        self.parser.add_argument('--disk_usage_rate_limit', default=85, action="store",
                                dest="DISK_USE_RATE_LIMIT", type=int,
                                help='disk use rate upper limit, '
                                'example: --disk_usage_rate_limit 85 means 85%%')
        self.parser.add_argument('--scan_log_intervel', default=30*60, action="store",
                                 dest="SCAN_LOG_INTERVEL", type=int,
                                 help='scan log interver, '
                                 'example: --scan_log_intervel 1800 means scan log per 30min')
        self.parser.add_argument('--least_driving_mode_duration', default=10*60, action="store",
                                 dest="LEAST_DRIVING_MODE_DURATION", type=int,
                                 help='filter out less than least driving mode duration, '
                                 'example: --least_driving_mode_duration 600 means filter out the duration less 10min')
        self.parser.add_argument('--clip_duration_margin', default=60, action="store",
                                 dest="CLIP_DURATION_MARGIN", type=int,
                                 help='clip margin of driving mode duration, '
                                 'example: --clip_duration_margin 60 means clip the duration 1min head and tail')
        self.parser.add_argument('--scan_disk_intervel', default=5*60, action="store",
                                 dest="SCAN_DISK_INTERVEL", type=int,
                                 help='scan disk use rate interver, '
                                 'example: --scan_disk_intervel 300 means scan log per 5min')
        self._args = None

    def args(self):
        """Get parsed args."""
        if self._args is None:
            self._args = self.parser.parse_args()
            LOGGER.info("args: {}".format(self._args))
        return self._args

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    arg_manager = ArgManager()
    args = arg_manager.args()
