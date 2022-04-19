
from singleton import singleton

@singleton
class Foo(object):
    def foo(self):
        pass

a = Foo()
b = Foo()
print(a == b)
print(id(a) == id(b))
