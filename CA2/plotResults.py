import matplotlib.pyplot as plt
import numpy as np

def plot():
    plt.figure(figsize=(12, 8))

    # xLabel = list(range(1, 100))
    through4 = np.genfromtxt("throughput4.tr", dtype=np.int32)
    through5 = np.genfromtxt("throughput5.tr", dtype=np.int32)
    through6 = np.genfromtxt("throughput6.tr", dtype=np.int32)
    
    yLabel = through4[:, 1]
    xLabel = through4[:, 0]
    plt.plot(xLabel, yLabel)
    plt.plot(xLabel, through5[:, 1])
    plt.plot(xLabel, through6[:, 1])
    
    plt.show()

plot()