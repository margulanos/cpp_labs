import numpy as np
import matplotlib.pyplot as plt
from math import *

def gr(path_N, path_time, nazvanie):
    with open(path_N, 'r') as file:
        data_N = file.read()
    data_N = data_N.splitlines()
    N = []
    for i in data_N:
        N.append(int(i))
    N = N[:28]
    N = np.array(N)
    with open(path_time, 'r') as file:
        data_time = file.read()
    data_time = data_time.splitlines()
    time = []
    for i in data_time:
        time.append(int(i))
    time = np.array(time)

    plt.ylabel("$t$", fontsize="12") 
    plt.xlabel("$N$", fontsize="12")
    plt.title(nazvanie) 
    plt.minorticks_on()
    plt.grid(True, "both", "both")
    plt.scatter(N, time, linewidths=0.3)
    
    plt.savefig(nazvanie)
    plt.show()
gr('C:/Users/HP/Desktop/proga/laby/N.txt', 'C:/Users/HP/Desktop/proga/laby/C_ner.txt','C_ner')
