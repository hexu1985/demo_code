# -*- coding:utf-8 -*-

import matplotlib as mpl
import matplotlib.pyplot as plt

mpl.rcParams["font.sans-serif"] = ["SimHei"]
mpl.rcParams["axes.unicode_minus"] = False

# some simple data
x = [1,2,3]
y = [0.730,1.878,3.017]
tick_label=["icmp","mqtt qos0","mqtt qos1"]

# create bar
plt.barh(x,y,align="center",color="c",tick_label=tick_label,hatch="/")

# set x,y_axis label
plt.xlabel("协议类型")
plt.ylabel("time(ms)")

plt.savefig('mqtt_perf_test')
plt.show()
