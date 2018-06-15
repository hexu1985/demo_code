import demo
import numpy as np

dic1 = {'whatever':1}
demo.test2(dic1)
print(dic1)
arr = np.array([1,2,3], dtype = np.float32)
print(arr.dtype)
print(arr)
demo.add_arr_1(arr, 1, 3)
print(arr)

