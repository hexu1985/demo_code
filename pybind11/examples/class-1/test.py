#!/usr/bin/env python3

from build import example

p = example.Pet("Molly")
print(p)
print(p.getName())
p.setName("Charly")
print(p.getName())
