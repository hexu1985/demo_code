from demo import *

x = X()
y = Y()
z = Z()
x.str = 'hello'
y.x = x
print(y.x.str)

x.str = 'world'
print(y.x.str)

z.value = 3
y.z = z
print(y.z_value())

z.value = 6
print(y.z_value())

x2 = f(y, z)
print(x2.str)

