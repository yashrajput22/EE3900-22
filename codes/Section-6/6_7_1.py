import numpy as np
from scipy.fft import fft, ifft
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def nlgn(n, a): return a*n*np.log2(n)
def nsq(n, a): return (a*n)**2

a = 2**(np.arange(21))
a1 = np.loadtxt('fft.txt', dtype='double')
a2 = np.loadtxt('ifft.txt', dtype='double')
b = np.linspace(1, 2**20 + 1, 2**20)
popt, pcov = curve_fit(nlgn, a, a2)
p1 = nlgn(b, *popt)
p2 = nsq(b, *popt)
p3 = np.log2(b)
#plots
plt.plot(a, a1, 'o')
plt.plot(a, a2, 'o')
plt.plot(b, p1)
plt.plot(b, p2)
plt.plot(b, p3)
plt.legend(["Simulation (FFT)", "Simulation (IFFT)", "Analysis (n$\log$n)", "Analysis (n$^2$)", "Analysis ($\log$n)"])
plt.xlabel('n')
plt.ylabel('T(n) (ms)')
plt.grid()# minor

#If using termux
#plt.savefig('../figs/6_7_1.png')
#subprocess.run(shlex.split("termux-open ../figs/yndft.pdf"))
#else
plt.show()