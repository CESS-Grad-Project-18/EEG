import pandas as pd
import matplotlib.pyplot as plt

def plot_data(i):
    v, a = [], []
    dataset = pd.read_pickle("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s" + str(i).rjust(2, '0') + ".dat")
    for j in range(40):
        v += [dataset['labels'][j][0]]
        a += [dataset['labels'][j][1]]
    plt.plot(v, a, 'bo')
    plt.title('Subject ' + str(i))
    plt.show()
    v, a = [], []
