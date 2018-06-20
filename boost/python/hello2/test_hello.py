import hello_ext

s = hello_ext.greet()
print(s)

#s = hello_ext.greet2()
#print(s)

vec = hello_ext.greet3()
ba = bytes(vec)
print(ba)

hello_ext.print(ba)

