import pandas as pd
import matplotlib.pyplot as plt

def plot_data(i):
    v, a = [], []
    dataset = pd.read_pickle("./s" + str(i).rjust(2, '0') + ".dat")
    for j in range(40):
        v += [dataset['labels'][j][0]]
        a += [dataset['labels'][j][1]]
    plt.plot(v, a, 'bo')
    plt.title('Subject ' + str(i))
    # plt.show()
    plt.savefig("./s"+str(i)+".png")
    plt.close()
    v, a = [], []

if __name__ == "__main__":
	for i in range(1,33):
		plot_data(i)