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
        traceback.print_exc(limit=1, file=sys.stdout)


if __name__ == '__main__':
    main()
