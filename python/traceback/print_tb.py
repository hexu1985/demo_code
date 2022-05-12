import sys
import traceback


def func1():
    raise NameError("--func1 exception--")


def main():
    try:
        func1()
    except Exception as e:
        exc_type, exc_value, exc_traceback_obj = sys.exc_info()
        traceback.print_tb(exc_traceback_obj)


if __name__ == '__main__':
    main()
