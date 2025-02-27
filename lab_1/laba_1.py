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
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/worst_linear.txt', 'worst_linear')
gr('C:/Users/HP/Desktop/proga/laby/N_binary.txt', 'C:/Users/HP/Desktop/proga/laby/worst_binary.txt', 'worst_binary')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/average_linear.txt', 'average_linear')
gr('C:/Users/HP/Desktop/proga/laby/N_binary.txt', 'C:/Users/HP/Desktop/proga/laby/average_binary.txt', 'average_binary')
gr('C:/Users/HP/Desktop/proga/laby/N_vtupuyu.txt', 'C:/Users/HP/Desktop/proga/laby/worst_vtupuyu.txt', 'worst_vtupuyu')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/worst_poumnomu.txt', 'worst_poumnomu')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/A.txt', 'A')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/B.txt', 'B')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/C.txt', 'C')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/A_ner.txt', 'A_ner')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/B_ner.txt', 'B_ner')
gr('C:/Users/HP/Desktop/proga/laby/N_linear.txt', 'C:/Users/HP/Desktop/proga/laby/C_ner.txt', 'C_ner')