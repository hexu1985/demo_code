import hello 

base = hello.Base()

# 定义派生类，继承C++类
class Derived(hello.Base):
    def f(self):
        return 42

derived = Derived()

print(base.f())
print(derived.f())

hello.b(base)
hello.b(derived)
