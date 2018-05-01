import pyedflib
import numpy as np
from scipy.fftpack import rfft, fftfreq, fft
import math
import sklearn
from sklearn.naive_bayes import GaussianNB
from scipy.signal import lfilter, firwin as fir1

def PredictAndPrint(test_ot,classifier,testlabels_ot,p):
    c =0
    for k in range(len(test_ot)):
        pr = classifier.predict(np.array([test_ot[k]]))
        if(p):
            print("Predicted: ", pr[0], " ,Correct Value: ", testlabels_ot[k] )
        if pr[0] == testlabels_ot[k]:
            c+=1
    print(c, "Correct out of ", len(testlabels_ot)," Percesion: " ,c/len(testlabels_ot)*100 )

def DifferentialEntropy(Signal):
    variance = np.var(Signal)
    return (0.5*np.log(2*math.pi*math.e*variance))

def FilterData(data,lower,higher):
    Fs = 105
    numtaps = 100
    Fn = Fs/2
    freq = np.array([lower, higher])/Fn
    coeff = fir1(numtaps, freq, pass_zero=False)
    filtered_signal = fft(lfilter(coeff, 1.0, data))
    return filtered_signal

def getLabels(f,a):
	annotations = a.readAnnotations()
	annotationPerSecond = []
	n=0
	for i in range(f.getFileDuration()):
		while(i > int(annotations[0][n]) + int(annotations[1][n])):
			n += 1
		if(annotations[2][n] == "Sleep stage W"):
			annotationPerSecond.append(0)
		elif(annotations[2][n] == "Sleep stage 1"):
			annotationPerSecond.append(1)
		elif(annotations[2][n] == "Sleep stage 2"):
			annotationPerSecond.append(2)
		elif(annotations[2][n] == "Sleep stage 3"):
			annotationPerSecond.append(3)
		elif(annotations[2][n] == "Sleep stage 4"):
			annotationPerSecond.append(4)
		elif(annotations[2][n] == "Sleep stage M"):
			annotationPerSecond.append(5)
		elif(annotations[2][n] == "Sleep stage R"):
			annotationPerSecond.append(6)
		elif(annotations[2][n] == "Sleep stage ?"):
			annotationPerSecond.append(7)
	return annotationPerSecond

def printsignal(signum,file):
	n = 200
	buf = f.readSignal(signum)
	print("Total Length : " + str(len(buf)) + "\n")
	print("Printing first 200 samples")
	result = ""
	for i in np.arange(n):
	    result += ("%.1f, " % buf[i])
	print(result)
	print("\n")

def printannotations(annotationfile):
	annotations = annotationfile.readAnnotations()
	for n in np.arange(a.annotations_in_file):
		print("annotation: onset is %f    duration is %s    description is %s" % (annotations[0][n],annotations[1][n],annotations[2][n]))

def printinfo(f,a):
	# rint("filetype: %i\n"%hdr.filetype);
	print("Number of Signals: %i" % f.signals_in_file)
	print(f.getSignalLabels())
	print("\n")

	print("file duration: %i seconds" % f.file_duration)
	print("startdate: %i-%i-%i" % (f.getStartdatetime().day,f.getStartdatetime().month,f.getStartdatetime().year))
	print("starttime: %i:%02i:%02i" % (f.getStartdatetime().hour,f.getStartdatetime().minute,f.getStartdatetime().second))
	print("datarecord duration: %f seconds" % f.getFileDuration())
	print("Sample Rate of EEG data: %f" % f.getSampleFrequency(1))
	print("number of datarecords in the file: %i" % f.datarecords_in_file)
	print("number of annotations in the file: %i" % a.annotations_in_file)
	print("\n")

f = pyedflib.EdfReader("SC4011E0-PSG.edf")
a = pyedflib.EdfReader("SC4011EH-Hypnogram.edf")

#printinfo(f,a)
printannotations(a)
#print("SIGNAL 0 - EEG Fpz-Cz\n")
#printsignal(0,f)
#print("SIGNAL 1 - EEG Pz-Oz\n")
#printsignal(1,f)

#Take every second, transform and get alpha,beta,gamma etc. sig)
annotationsPerSecond = getLabels(f,a)
#print(annotationsPerSecond)
buf1 = f.readSignal(0)
buf2 = f.readSignal(1)


readings = []
for i in range(f.getFileDuration()):
	print(i)
	start = i*100
	end = start+100
	data = []
	for j in range(0,1):
		if(j == 0):
			sig = buf1[start:end]
		else:
			sig = buf2[start:end]
		Delta_channel = FilterData(sig,0.5,4)
		delta = DifferentialEntropy(Delta_channel)

		Gamma_channel = FilterData(sig, 30, 50);
		gamma = DifferentialEntropy(Gamma_channel)

		Alpha_channel = FilterData(sig, 8, 13);
		alpha = DifferentialEntropy(Alpha_channel)

		Beta_channel = FilterData(sig, 13, 30);
		beta = DifferentialEntropy(Beta_channel)

		Theta_channel = FilterData(sig, 4, 8);
		theta = DifferentialEntropy(Theta_channel)

		data.append([delta, theta, alpha, beta, gamma])
	readings.append(np.array(data).flatten().tolist())

data_ot = readings[0:int(0.75*len(readings))]
labels_ot = annotationsPerSecond[0:int(0.75*len(annotationsPerSecond))]
test_ot = readings[int(0.75*len(readings)):]
testlabels_ot = annotationsPerSecond[int(0.75*len(annotationsPerSecond)):]


classifier=sklearn.naive_bayes.GaussianNB()
classifier.fit(np.array(data_ot), np.array(labels_ot))
PredictAndPrint(test_ot,classifier,testlabels_ot,0)

