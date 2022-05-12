import sys
import traceback


def func1():
    raise NameError("--func1 exception--")

def func2():
    func1()

def main():
    try:
        func2()
    except Exception as e:
        exc_type, exc_value, exc_traceback_obj = sys.exc_info()
        traceback.print_exception(exc_type, exc_value, exc_traceback_obj, limit=2, file=sys.stdout)


if __name__ == '__main__':
    main()
