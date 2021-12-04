import matplotlib.pyplot as plt
import numpy as np

x = np.array([-3,-4,2,4,5, 3])
y = np.array([ 5,-2,5,3,2,-4])

plt.plot(x, y, 'o') # 绘制点
plt.grid(linestyle=":") # 网格线
plt.axis([-7,7,-7,7])   # 自定义坐标轴范围[xmin, xmax, ymin, ymax]
#plt.xlim(-7,7)
#plt.ylim(-7,7)

plt.xticks(range(-7,8)) # x轴刻度
plt.yticks(range(-7,8)) # y轴刻度

plt.show()
