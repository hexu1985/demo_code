class SingletonMeta(type):
    __instance = None
    def __call__(cls,*args,**kwargs):
        if not cls.__instance:
            cls.__instance = type.__call__(cls,*args,**kwargs)
        return cls.__instance

class myclass(metaclass = SingletonMeta):
    def foo(self):
        pass

a = myclass()
b = myclass()
print(a==b)
print(id(a)==id(b))
