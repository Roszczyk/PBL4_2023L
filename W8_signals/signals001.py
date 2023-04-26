import numpy as np
import matplotlib.pyplot as plt

t=np.arange(100)
s=np.sin(0.99*2*np.pi*t)

plt.figure(0)
plt.plot(s, ".-")

plt.show()