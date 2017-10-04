import pickle
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import buttord, butter, zpk2sos, lfilter
from scipy.fftpack import rfft, fftfreq, fft


file = open("s01.dat","rb")
data = pickle.load(file,encoding = "latin1")
file.close()
Fs = 128
t = np.linspace(0,63,8064)
# transformed_signal = np.fft.fft(data["data"][0][0])
transformed_signal = np.abs(np.fft.fftshift(np.fft.fft(data["data"][0][1])))
Omega = fftfreq(len(transformed_signal), d=t[1]-t[0])
Sums = []
Passed = transformed_signal.copy()
Passed[(Omega>4)] = 0
Passed[(Omega<0.5)] = 0
Sums.append(np.trapz(Passed))
#############
Passed = transformed_signal.copy()
Passed[(Omega>8)] = 0
Passed[(Omega<4)] = 0
Sums.append(np.trapz(Passed))
###############
Passed = transformed_signal.copy()
Passed[(Omega>13)] = 0
Passed[(Omega<8)] = 0
Sums.append(np.trapz(Passed))
#[n, Wn] = buttord(np.array([5.0,13.0])/64, np.array([4.5, 13.5])/64, 4, 14)
#[b, a] = butter(n, Wn, 'bandpass')
#sig = lfilter(b,a,transformed_signal)
# print(np.arange(0,len(transformed_signal),128.0/8064.0))
# plt.plot(np.arange(-64.0,64.0,128.0/8064.0), transformed_signal)
# plt.show()
# print(len(sig))
print(np.arange(0,len(transformed_signal),128.0/8064.0))
plt.plot(np.linspace(0,128,len(Passed)), Passed)
plt.show()
print(Sums)
#0, 2, 3, 4, 5, 16, 18, 19, 20, 21, 22
#Ramo send this file