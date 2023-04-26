import numpy as np
import matplotlib.pyplot as plt

Fs=10000
s=np.loadtxt("signal.txt", delimiter=",")
N=s.shape[0]
T=N/Fs
n=np.arange(Fs*T)
t=n/Fs

plt.figure(0)
plt.plot(t,s, ".-")
plt.xlabel("Czas[s]")
plt.show()