from functools import wraps

def singleton(cls):
    instances = {}
    @wraps(cls)
    def getinstance(*args, **kwargs):
        if cls not in instances:
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    return getinstance

@singleton
class singleCls(object):
    def foo(self):
        pass

a = singleCls()
b = singleCls()
print(a == b)
print(id(a) == id(b))
