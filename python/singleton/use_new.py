class Singleton(object):
    __instance = None
    def __new__(cls,*args,**kwargs):
        if not cls. __instance:
            cls.__instance = super().__new__(cls,*args,**kwargs)
        return cls.__instance

a = Singleton()
b = Singleton()
print(a == b)
print(id(a) == id(b))
