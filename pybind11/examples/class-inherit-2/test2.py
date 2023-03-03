#!/usr/bin/env python3

from example import *

d = Dog()
print(call_go(d))

class Cat(Animal):
    def go(self, n_times):
        return "meow! " * n_times

c = Cat()
print(call_go(c))


