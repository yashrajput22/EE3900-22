import numpy as np
from scipy.fft import fft, ifft
import matplotlib.pyplot as plt


N = 14
n = np.arange(N)
fn=(-1/2)**n
hn1=np.pad(fn, (0,2), 'constant', constant_values=(0,0))
hn2=np.pad(fn, (2,0), 'constant', constant_values=(0,0))
h = hn1+hn2
xtemp=np.array([1.0,2.0,3.0,4.0,2.0,1.0])
x=np.pad(xtemp, (0,10), 'constant', constant_values=(0))
X = fft(x)
H = fft(h)
Y = H*X
y = ifft(Y).real
#plots
plt.stem(range(0,16),y)
plt.xlabel('$n$')
plt.ylabel('$y(n)$')
plt.grid()# minor

#If using termux
#plt.savefig('../figs/6_4.png')
plt.show()