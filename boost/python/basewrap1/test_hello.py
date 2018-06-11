import hello 

base = hello.Base()

# 定义派生类，继承C++类
class Derived(hello.Base):
    def f(self):
        return 42

derived = Derived()

#print(base.f())    # error!
#hello.b(base)      # error!

print(derived.f())
hello.b(derived)
