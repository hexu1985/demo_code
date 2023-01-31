#!/usr/bin/env python3

DATA_PULLER_ERROR_BEGIN = 1000
DATA_PULLER_NO_REMOTE_DATA = DATA_PULLER_ERROR_BEGIN + 1
DATA_PULLER_COLLECT_DATA_ERROR = DATA_PULLER_ERROR_BEGIN + 2
DATA_PULLER_PULL_DATA_ERROR = DATA_PULLER_ERROR_BEGIN + 3
DATA_PULLER_POSTPROCESS_DATA_ERROR = DATA_PULLER_ERROR_BEGIN + 4
DATA_PULLER_ERROR_END = 2000

class DataPullerException(Exception):
    def __init__(self, error_code, error_message):
        self.error_code = error_code
        self.error_message = error_message

    def __str__(self):
        return "error({}): {}".format(self.error_code, self.error_message)


def test_except(error):
    try:
        raise error
    except DataPullerException as e:
        print("got DataPullerException, {}".format(e))
    except Exception as e:
        print("got Exception, {}".format(e))

if __name__ == "__main__":
    test_except(DataPullerException(DATA_PULLER_NO_REMOTE_DATA, "no data"))
    test_except(Exception("no data"))
