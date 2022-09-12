import numpy as np
from scipy.fft import fft, ifft
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def nlgn(n, a): return a*n*np.log2(n)
def nsq(n, a): return a*n*n
def lg(n, a): return a*np.log2(n)

x = np.linspace(10, 1001, 100)
a = np.loadtxt('conv.txt', dtype='double')
popt, pcov = curve_fit(nsq, x, a)
p1 = nlgn(x, *popt)
p2 = nsq(x, *popt)
p3 = lg(x, *popt)
#plots
plt.plot(x, a, '.')
plt.plot(x, p1)
plt.plot(x, p2)
plt.plot(x, p3)
plt.xlabel('n')
plt.ylabel('T(n) (s)')
plt.legend(["Simulation (convolution)", "Analysis (n$\log$n)", "Analysis (n$^2$)", "Analysis ($\log$n)"])
plt.grid()# minor

#If using termux
#plt.savefig('../figs/6_7_2.png')
#subprocess.run(shlex.split("termux-open ../figs/yndft.pdf"))
#else
plt.show()