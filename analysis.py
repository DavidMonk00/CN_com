import numpy as np
import matplotlib.pyplot as plt
import os
import csv
import sys

f = [file for file in os.listdir("./data/") if file.endswith("height.dat")]
f.sort()
filename = f[-1]

x = np.loadtxt("./data/"+filename)
for i in range(7):
    plt.plot(x[i])
plt.xscale('log')
plt.yscale('log')
plt.show()
