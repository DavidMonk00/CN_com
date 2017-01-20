import numpy as np
import matplotlib.pyplot as plt
import os
import csv
import sys

f = [file for file in os.listdir("./data/") if file.endswith(".dat")]
f.sort()
filename = f[-1]

x = np.loadtxt("./data/"+filename)
plt.plot(x)
plt.show()
