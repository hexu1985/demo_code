import matplotlib.pyplot as plt
import numpy as np

x = np.array([-2,-1,0,1,2])
y = np.array([-3,-1,1,3,5])

plt.plot(x, y, marker = 'o', label="y=2x+1")
plt.legend()

plt.xlim(-5,5)
plt.ylim(-5,6)
plt.grid()
plt.show()
