import logging
import sys
import traceback
logger = logging.getLogger("traceback_test")

def func1():
    raise NameError("--func1 exception--")

def func2():
    func1()

def main():
    try:
        func2()
    except Exception as e:
        logger.error(traceback.format_exc(limit=1))


if __name__ == '__main__':
    main()
