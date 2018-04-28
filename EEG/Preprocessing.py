import pickle
import numpy as np
import math
from scipy import nanmean
from scipy.signal import lfilter, decimate, firwin as fir1
from scipy.fftpack import rfft, fftfreq, fft
import warnings
calcMethod = "DE"
SymetricMethod = "None"

def SymetricCalc(values):
    if(SymetricMethod == "None"):
        return np.array(values).flatten().tolist()
    if(SymetricMethod == "DASM"):
        return np.array(subHorizontal(values)).flatten().tolist()
    if(SymetricMethod == "RASM"):
        return np.array(subVertical(values)).flatten().tolist()
    if(SymetricMethod == "DCAU"):
        return np.array(divHorizontal(values)).flatten().tolist()
    
def CARFilter(channel_data):
    """
    Function that performs common average reference filtering on collected EEG signal
	(Applied after signal collection)
    :param channel_data: The array containing the EEG channel signals (AF3, AF4,Oz, etc.)
    :return: Array containing channels after CAR filter has been applied to them
    """
	data_size = len(channel_data)
	car_channel_data = np.zeros_like(channel_data)
	for i in range(data_size):
		car_channel = np.zeros_like(channel_data[0])
		for j in range(data_size):
			if(i != j):
				car_channel = np.add(car_channel, channel_data[j])
		car_channel_data[i] = channel_data[i] - np.divide(car_channel, float(data_size - 1))
	return car_channel_data

def decimate_signal(signal, old_sample_rate = 256, new_sample_rate = 128, ds_type = 'Mean'):
    """ Function that downsamples signal.
    
    :param signal: list including decimated_signal with sample signal
    :param sample_rate: desired sample_rate
    :param ds_type: Type of interpolating used for downsampling. (Mean or IIR)
    :returns decimated_signal: downsampled signal, in same format as input signal
    """

    decimated_signal = []
    SR = int(np.round(float(old_sample_rate)/float(new_sample_rate)))
    if ds_type == 'Mean':
        for sample in signal:
            pad_size = int(math.ceil(float(sample.size) / SR) * SR - sample.size)
            s_padded = np.append(sample, np.zeros(pad_size) * np.NaN)
            s_new = nanmean(s_padded.reshape(-1, SR), axis=1)
            decimated_signal = np.append(decimated_signal, s_new)
    elif ds_type == 'IIR':
        decimated_signal = decimate(signal, SR)
    return decimated_signal

def FilterData(data,lower,higher):
    Fs = 128.0
    numtaps = 100
    Fn = Fs/2
    freq = np.array([lower, higher])/Fn
    coeff = fir1(numtaps, freq, pass_zero=False)
    filtered_signal = fft(lfilter(coeff, 1.0, data))
    return filtered_signal
    # for i in range(np.size(signal,1))
        # f_d[i, :] = fft(lfilter(coeff, 1.0, signal))

def BandCalc(band):
    if(calcMethod == "DE"):
        res = DifferentialEntropy(band)
    elif(calcMethod == "TR"):
        res = np.trapz(band)
    return res

def subVertical(values):
    diff = []
    diff.append(abs(np.subtract(values[0], values[13])).tolist())
    diff.append(abs(np.subtract(values[1], values[12])).tolist())
    diff.append(abs(np.subtract(values[2], values[10])).tolist())
    diff.append(abs(np.subtract(values[3], values[11])).tolist())
    diff.append(abs(np.subtract(values[4],values[8])).tolist())
    diff.append(abs(np.subtract(values[5],values[9])).tolist())
    diff.append(abs(np.subtract(values[16],values[31])).tolist())
    diff.append(abs(np.subtract(values[17],values[30])).tolist())
    diff.append(abs(np.subtract(values[18],values[15])).tolist())
    diff.append(abs(np.subtract(values[19],values[28])).tolist())
    diff.append(abs(np.subtract(values[20],values[29])).tolist())
    diff.append(abs(np.subtract(values[21],values[26])).tolist())
    diff.append(abs(np.subtract(values[22],values[27])).tolist())
    return diff

def subHorizontal(values):
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

def divHorizontal(values):
    diff = []
    diff.append(abs(np.divide(values[0], values[16])).tolist())
    diff.append(abs(np.divide(values[1], values[17])).tolist())
    diff.append(abs(np.divide(values[2], values[19])).tolist())
    diff.append(abs(np.divide(values[3], values[20])).tolist())
    diff.append(abs(np.divide(values[4], values[21])).tolist())
    diff.append(abs(np.divide(values[5], values[22])).tolist())
    diff.append(abs(np.divide(values[6], values[24])).tolist())
    diff.append(abs(np.divide(values[7], values[25])).tolist())
    diff.append(abs(np.divide(values[8], values[26])).tolist())
    diff.append(abs(np.divide(values[9], values[27])).tolist())
    diff.append(abs(np.divide(values[10], values[28])).tolist())
    diff.append(abs(np.divide(values[11], values[29])).tolist())
    diff.append(abs(np.divide(values[12], values[30])).tolist())
    diff.append(abs(np.divide(values[13], values[31])).tolist())
    return diff

def DifferentialEntropy(Signal):
    variance = np.var(Signal)
    return (0.5*np.log(2*math.pi*math.e*variance))


def processReadings(data):
    t = np.linspace(0, 63, 8064)
    readings = []
    for j in range(len(data)):    #LOOP ON VIDEOS
        values =[]
        for i in range(40):       #LOOP ON CHANNELS
            Delta_channel = FilterData(data[j][i],0.5,4)
            delta = BandCalc(Delta_channel)

            Gamma_channel = FilterData(data[j][i], 30, 50);
            gamma = BandCalc(Gamma_channel)

            Alpha_channel = FilterData(data[j][i], 8, 13);
            alpha = BandCalc(Alpha_channel)

            Beta_channel = FilterData(data[j][i], 13, 30);
            beta = BandCalc(Beta_channel)

            Theta_channel = FilterData(data[j][i], 4, 8);
            theta = BandCalc(Theta_channel)

            """transformed_signal = np.abs(np.fft.fftshift(np.fft.fft(data[j][i])))
            Omega = fftfreq(len(transformed_signal), d=t[1] - t[0])
            Delta_channel = transformed_signal.copy()
            Delta_channel[(Omega > 4)] = 0
            Delta_channel[(Omega < 0.5)] = 0
            dc = Filterfunction(Delta_channel)
            delta = BandCalc(Delta_channel)

            Theta_channel = transformed_signal.copy()
            Theta_channel[(Omega > 8)] = 0
            Theta_channel[(Omega < 4)] = 0
            theta = BandCalc(Theta_channel)

            Alpha_channel = transformed_signal.copy()
            Alpha_channel[(Omega > 13)] = 0
            Alpha_channel[(Omega < 8)] = 0

            alpha = BandCalc(Alpha_channel)

            Beta_channel = transformed_signal.copy()
            Beta_channel[(Omega > 30)] = 0
            Beta_channel[(Omega < 13)] = 0
            beta = BandCalc(Beta_channel)

            Gamma_channel = transformed_signal.copy()
            Gamma_channel[(Omega > 50)] = 0
            Gamma_channel[(Omega < 30)] = 0
            gamma = BandCalc(Gamma_channel)"""

            values.append([delta, theta, alpha, beta, gamma])
        
        readings.append(SymetricCalc(values))
        #readings.append(np.array(sub(values)).flatten().tolist())
    return readings

def processLabels(data):
    results=[]
    for i in range(len(data)):
        results.append(data[i][0:2].tolist())

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
