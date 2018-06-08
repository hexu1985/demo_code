import hello

planet = hello.World("hollo world")
s = planet.greet()
print(s)
planet.set('howdy')
s = planet.greet()
print(s)
