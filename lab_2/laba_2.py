import numpy as np
import matplotlib.pyplot as plt
from math import *


def mnk(x, y):
    s_x2 = np.mean(x ** 2)
    s_xy = np.mean(x * y)
    s_y2 = np.mean(y ** 2)
    s_x = np.mean(x)
    s_y = np.mean(y)

    k = (s_xy - s_x * s_y) / (s_x2 - s_x ** 2)
    b = s_y - k * s_x
    
    r = (s_xy - s_x * s_y) / (sqrt(s_x2 - s_x ** 2) * sqrt(s_y2 - s_y ** 2))
    return [k, b, r]


def shaker(path_N, path_shaker, path_puzyrok, nazvanie, save, y):
    N = np.loadtxt(path_N)
    shaker = np.loadtxt(path_shaker)
    puzyrok = np.loadtxt(path_puzyrok)
    ln_N = np.log(N)
    ln_shaker = np.log(shaker)
    k_shaker, b_shaker, r_shaker = mnk(ln_N, ln_shaker)
    c_shaker = np.exp(b_shaker)
    ln_puzyrok = np.log(puzyrok)
    k_puzyrok, b_puzyrok, r_puzyrok = mnk(ln_N, ln_puzyrok)
    c_puzyrok = np.exp(b_puzyrok)

    edizm1 = ''
    edizm2 = ''
    mnozh = 1
    if y == 't':
        edizm1 = ', ms'
        edizm2 = ' ns'
        mnozh = 1e6
    plt.figure()
    plt.ylabel(f"${y}$"+edizm1, fontsize="12") 
    plt.xlabel("$N$", fontsize="12")
    plt.title(nazvanie) 
    plt.minorticks_on()
    plt.grid(True, "both", "both")
    plt.scatter(N, shaker, c = 'b', s = 5, label = "Шейкерная сортировка")
    plt.scatter(N, puzyrok, c = 'g', s = 5, label = "Пузырьковая сортировка")
    x = np.linspace(0.95 * min(N), 1.03 * max(N), 200)
    plt.plot(x, c_shaker * x ** k_shaker, c = 'r', label = f"Шейкерная сортировка ${y} = {c_shaker*mnozh:.2f}$" r"$\cdot N^{" f"{k_shaker:.2f}" r"}$"+edizm2)
    plt.plot(x, c_puzyrok * x ** k_puzyrok, c = 'orange', label = f"Пузырьковая сортировка ${y} = {c_puzyrok*mnozh:.2f}$" r"$\cdot N^{" f"{k_puzyrok:.2f}" r"}$"+edizm2)
    plt.legend()
    plt.savefig(save, dpi = 600)
    
    
    text_box = (
    r"$r_\text{ш}$" f"$ = {r_shaker:.4f}$\n"
    r"$r_\text{п}$" f"$ = {r_puzyrok:.4f}$"
    )
    plt.figure()
    plt.text(0.65, 0.2, text_box, transform=plt.gca().transAxes, fontsize=10, verticalalignment='top', bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))
    plt.ylabel(r"$\ln{"+y+r"}$", fontsize="12") 
    plt.xlabel("$\ln{N}$", fontsize="12")
    plt.title(nazvanie) 
    plt.minorticks_on()
    plt.grid(True, "both", "both")
    plt.scatter(ln_N, ln_shaker, c = 'b', s = 5, label = "Шейкерная сортировка", zorder = 3)
    plt.scatter(ln_N, ln_puzyrok, c = 'g', s = 5, label = "Пузырьковая сортировка", zorder = 3)
    x = np.array([0.95 * min(ln_N), 1.03 * max(ln_N)])
    plt.plot(x, k_shaker * x + b_shaker, color = 'r', label = f"Шейкерная " r"$\ln{"+y+r"}$" f"$= {k_shaker:.2f}\cdot$" r"$\ln{N}$" f"$ {b_shaker:.2f}$")
    plt.plot(x, k_puzyrok * x + b_puzyrok, color = 'orange', label = f"Пузырьковая " r"$\ln{"+y+r"}$" f"$= {k_puzyrok:.2f}\cdot$" r"$\ln{N}$" f"$ {b_puzyrok:.2f}$")
    plt.legend()
    plt.savefig(save+'_ln', dpi = 600)
    
#shaker('N.txt', 'shaker_mid.txt', 'puzyrok_mid.txt', "Шейкерная и пузырьковая сортировки", 'part1_time', 't')
#shaker('N.txt', 'shaker_swap.txt', 'puzyrok_swap.txt', "Шейкерная и пузырьковая сортировки", 'part1_swaps', 'swaps')



def comb(path_N, path_comb, path_puzyrok, nazvanie, save, y):
    N = np.loadtxt(path_N)
    comb = np.loadtxt(path_comb)
    puzyrok = np.loadtxt(path_puzyrok)
    ln_N = np.log(N)
    ln_comb = np.log(comb)
    k_comb, b_comb, r_comb = mnk(ln_N, ln_comb)
    c_comb = np.exp(b_comb)
    ln_puzyrok = np.log(puzyrok)
    k_puzyrok, b_puzyrok, r_puzyrok = mnk(ln_N, ln_puzyrok)
    c_puzyrok = np.exp(b_puzyrok)

    edizm1 = ''
    edizm2 = ''
    mnozh = 1
    if y == 't':
        edizm1 = ', ms'
        edizm2 = ' ns'
        mnozh = 1e6
    plt.figure()
    plt.ylabel(f"${y}$"+edizm1, fontsize="12") 
    plt.xlabel("$N$", fontsize="12")
    plt.title(nazvanie) 
    plt.minorticks_on()
    plt.grid(True, "both", "both")
    plt.scatter(N, comb, c = 'b', s = 5, label = "Сортировка расческой")
    plt.scatter(N, puzyrok, c = 'g', s = 5, label = "Сортировка пузырьком")
    x = np.linspace(0.95 * min(N), 1.03 * max(N), 200)
    plt.plot(x, c_comb * x ** k_comb, c = 'r', label = f"Сортировка расческой ${y} = {c_comb*mnozh:.2f}$" r"$\cdot N^{" f"{k_comb:.2f}" r"}$"+edizm2)
    plt.plot(x, c_puzyrok * x ** k_puzyrok, c = 'orange', label = f"Сортировка пузырьком ${y} = {c_puzyrok*mnozh:.2f}$" r"$\cdot N^{" f"{k_puzyrok:.2f}" r"}$"+edizm2)
    plt.legend()
    plt.savefig(save, dpi = 600)
    
    
    
    text_box = (
    r"$k_\text{р}$" f"$ = {k_comb:.2f}$\n"
    r"$r_\text{р}$" f"$ = {r_comb:.4f}$\n"
    r"$k_\text{п}$" f"$ = {k_puzyrok:.2f}$\n"
    r"$r_\text{п}$" f"$ = {r_puzyrok:.4f}$"
    )
    plt.figure()
    plt.text(0.65, 0.2, text_box, transform=plt.gca().transAxes, fontsize=10, verticalalignment='top', bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))
    plt.ylabel(r"$\ln{"+y+r"}$", fontsize="12") 
    plt.xlabel("$\ln{N}$", fontsize="12")
    plt.title(nazvanie) 
    plt.minorticks_on()
    plt.grid(True, "both", "both")
    plt.scatter(ln_N, ln_comb, c = 'b', s = 5, label = "Сортировка расческой", zorder = 3)
    plt.scatter(ln_N, ln_puzyrok, c = 'g', s = 5, label = "Сортировка пузырьком", zorder = 3)
    x = np.array([0.95 * min(ln_N), 1.03 * max(ln_N)])
    plt.plot(x, k_comb * x + b_comb, color = 'r', label = f"Расческа " r"$\ln{"+y+r"}$" f"$= {k_comb:.2f}\cdot$" r"$\ln{N}$" f"$ {b_comb:.2f}$")
    plt.plot(x, k_puzyrok * x + b_puzyrok, color = 'orange', label = f"Пузырьком " r"$\ln{"+y+r"}$" f"$= {k_puzyrok:.2f}\cdot$" r"$\ln{N}$" f"$ {b_puzyrok:.2f}$")
    plt.legend()
    plt.savefig(save+'_ln', dpi = 600)
    
#comb('N.txt', 'comb_mid.txt', 'puzyrok_mid.txt', "Сортировки расческой и пузырьком", 'part2_time', 't')
#comb('N.txt', 'comb_swap.txt', 'puzyrok_swap.txt', "Сортировки расческой и пузырьком", 'part2_swap', 'swaps')



def shell(path_N, path_shell1, path_shell2, path_shell3, nazvanie, save, y):
    N = np.loadtxt(path_N)
    ln_N = np.log(N)
    shell1 = np.loadtxt(path_shell1)
    ln_shell1 = np.log(shell1)
    k_shell1, b_shell1, r_shell1 = mnk(ln_N, ln_shell1)
    c_shell1 = np.exp(b_shell1)
    
    shell2 = np.loadtxt(path_shell2)
    ln_shell2 = np.log(shell2)
    k_shell2, b_shell2, r_shell2 = mnk(ln_N, ln_shell2)
    c_shell2 = np.exp(b_shell2)
    
    shell3 = np.loadtxt(path_shell3)
    ln_shell3 = np.log(shell3)
    k_shell3, b_shell3, r_shell3 = mnk(ln_N, ln_shell3)
    c_shell3 = np.exp(b_shell3)

    edizm1 = ''
    edizm2 = ''
    mnozh = 1
    if y == 't':
        edizm1 = ', ms'
        edizm2 = ' ns'
        mnozh = 1e6
    plt.figure()
    plt.ylabel(f"${y}$"+edizm1, fontsize="12") 
    plt.xlabel("$N$", fontsize="12")
    plt.title(nazvanie) 
    plt.minorticks_on()
    plt.grid(True, "both", "both")
    plt.scatter(N, shell1, c = 'b', s = 5, label = "Сортировка Шелла 1")
    plt.scatter(N, shell2, c = 'g', s = 5, label = "Сортировка Шелла 2")
    plt.scatter(N, shell3, c = 'purple', s = 5, label = "Сортировка Шелла 3")
    x = np.linspace(0.95 * min(N), 1.03 * max(N), 200)
    plt.plot(x, c_shell1 * x ** k_shell1, c = 'r', label = f"Шелл 1 ${y} = {c_shell1*mnozh:.2f}$" r"$\cdot N^{" f"{k_shell1:.2f}" r"}$"+edizm2)
    plt.plot(x, c_shell2 * x ** k_shell2, c = 'orange', label = f"Шелл 2 ${y} = {c_shell2*mnozh:.2f}$" r"$\cdot N^{" f"{k_shell2:.2f}" r"}$"+edizm2)
    plt.plot(x, c_shell3 * x ** k_shell3, c = 'yellow', label = f"Шелл 3 ${y} = {c_shell3*mnozh:.2f}$" r"$\cdot N^{" f"{k_shell3:.2f}" r"}$"+edizm2)
    plt.legend()
    plt.savefig(save, dpi = 600)
    
    
    
    text_box = (
    r"$k_1$" f"$ = {k_shell1:.2f}$\n"
    r"$r_1$" f"$ = {r_shell1:.4f}$\n"
    r"$k_2$" f"$ = {k_shell2:.2f}$\n"
    r"$r_2$" f"$ = {r_shell2:.4f}$\n"
    r"$k_3$" f"$ = {k_shell3:.2f}$\n"
    r"$r_3$" f"$ = {r_shell3:.4f}$\n"
    )
    plt.figure()
    plt.text(0.65, 0.4, text_box, transform=plt.gca().transAxes, fontsize=10, verticalalignment='top', bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))
    plt.ylabel(r"$\ln{"+y+r"}$", fontsize="12") 
    plt.xlabel("$\ln{N}$", fontsize="12")
    plt.title(nazvanie) 
    plt.minorticks_on()
    plt.grid(True, "both", "both")
    plt.scatter(ln_N, ln_shell1, c = 'b', s = 5, label = "Сортировка Шелла 1", zorder = 3)
    plt.scatter(ln_N, ln_shell2, c = 'g', s = 5, label = "Сортировка Шелла 2", zorder = 3)
    plt.scatter(ln_N, ln_shell3, c = 'purple', s = 5, label = "Сортировка Шелла 3", zorder = 3)
    x = np.array([0.95 * min(ln_N), 1.03 * max(ln_N)])
    plt.plot(x, k_shell1 * x + b_shell1, color = 'r', label = f"Шелл 1 " r"$\ln{"+y+r"}$" f"$= {k_shell1:.2f}\cdot$" r"$\ln{N}$" f"$ {b_shell1:.2f}$")
    plt.plot(x, k_shell2 * x + b_shell2, color = 'orange', label = f"Шелл 2 " r"$\ln{"+y+r"}$" f"$= {k_shell2:.2f}\cdot$" r"$\ln{N}$" f"$ {b_shell2:.2f}$")
    plt.plot(x, k_shell3 * x + b_shell3, color = 'yellow', label = f"Шелл 3 " r"$\ln{"+y+r"}$" f"$= {k_shell3:.2f}\cdot$" r"$\ln{N}$" f"$ {b_shell3:.2f}$")
    plt.legend()
    plt.savefig(save+'_ln', dpi = 600)
    
shell('N_shell.txt', 'shell1_mid.txt', 'shell2_mid.txt', 'shell3_mid.txt', "Сортировки Шелла", 'part3_time', 't')
shell('N_shell.txt', 'shell1_swap.txt', 'shell2_swap.txt', 'shell3_swap.txt', "Сортировки Шелла", 'part3_swap', 'swaps')