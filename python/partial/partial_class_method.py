from functools import partial

class A:
    def __init__(self):
        pass

    def add(self, *args):
        return sum(args)

a = A()

add_100 = partial(a.add, 100)
print(add_100(1, 2, 3))  # 106

add_101 = partial(a.add, 101)
print(add_101(1, 2, 3))  # 107
