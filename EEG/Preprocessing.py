import pickle
import numpy as np
from scipy.fftpack import rfft, fftfreq, fft
import warnings

def sub(values):
    diff = []

    diff.append(abs(np.subtract(values[0], values[16])).tolist())
    diff.append(abs(np.subtract(values[1], values[17])).tolist())

    diff.append(abs(np.subtract(values[2], values[19])).tolist())
    diff.append(abs(np.subtract(values[3], values[20])).tolist())
    diff.append(abs(np.subtract(values[4], values[21])).tolist())
    diff.append(abs(np.subtract(values[5], values[22])).tolist())

    diff.append(abs(np.subtract(values[6], values[24])).tolist())
    diff.append(abs(np.subtract(values[7], values[25])).tolist())
    diff.append(abs(np.subtract(values[8], values[26])).tolist())
    diff.append(abs(np.subtract(values[9], values[27])).tolist())
    diff.append(abs(np.subtract(values[10], values[28])).tolist())
    diff.append(abs(np.subtract(values[11], values[29])).tolist())
    diff.append(abs(np.subtract(values[12], values[30])).tolist())
    diff.append(abs(np.subtract(values[13], values[31])).tolist())
    
    return diff


def getData(data): # data of a single person file
    t = np.linspace(0, 63, 8064)
    readings = []
    for j in range(len(data)):   # loop over each video
        values =[]
        for i in range(40):     # loop over each channel
            transformed_signal = np.abs(np.fft.fftshift(np.fft.fft(data[j][i])))
            Omega = fftfreq(len(transformed_signal), d=t[1] - t[0])
            Delta_channel = transformed_signal.copy()

            """
            We extract 5 frequencies: Delta, Theta, Alpha, Beta, Gamma
            We apply a band pass filter to have the wanted frequency.
            Then we sum it up.
            """

            # Band Passing
            Delta_channel[(Omega > 4)] = 0
            Delta_channel[(Omega < 0.5)] = 0
            # Summing
            delta = np.trapz(Delta_channel)

            Theta_channel = transformed_signal.copy()
            Theta_channel[(Omega > 8)] = 0
            Theta_channel[(Omega < 4)] = 0
            theta = np.trapz(Theta_channel)

            Alpha_channel = transformed_signal.copy()
            Alpha_channel[(Omega > 13)] = 0
            Alpha_channel[(Omega < 8)] = 0
            alpha = np.trapz(Alpha_channel)

            Beta_channel = transformed_signal.copy()
            Beta_channel[(Omega > 30)] = 0
            Beta_channel[(Omega < 13)] = 0
            beta = np.trapz(Beta_channel)

            Gamma_channel = transformed_signal.copy()
            Gamma_channel[(Omega > 50)] = 0
            Gamma_channel[(Omega < 30)] = 0
            gamma = np.trapz(Gamma_channel)

            values.append([delta, theta, alpha, beta, gamma])
        readings.append(np.array(sub(values)).flatten().tolist())
    return readings

def getLabels(data):
    results=[]

    # extracting arousals and valencies they are the first two elements in each list of labels
    for i in range(len(data)):
        results.append(data[i][0:2].tolist())


    """
            x(0,10)
            |
        2   |   1
     -------|-------
        3   |   4
            |
            x(0,5)
    """

    for i in range(len(results)):
        if results[i][0] >= 5 and results[i][1] >= 5:
            results[i] = 1
        elif results[i][0] < 5 and results[i][1] >= 5:  
            results[i] = 2
        elif results[i][0] < 5 and results[i][1] < 5: 
            results[i] = 3
        elif results[i][0] >= 5 and results[i][1] < 5:
            results[i] = 4
    return results
