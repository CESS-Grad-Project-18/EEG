import numpy as np
import Preprocessing
import pickle
from sklearn import svm
from sklearn.naive_bayes import GaussianNB
import matplotlib.pyplot as plt
import warnings
from sklearn.preprocessing import RobustScaler
import math
warnings.filterwarnings("ignore")

data_ot = []
labels_ot = []
test_ot=[]
testlabels_ot=[]
ones=0
twos=0
threes=0
fours=0
for i in range(1,33):
    if i<10:
        file = open("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s0"+str(i)+".dat", "rb")
    else:
        file = open("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s" +str(i) + ".dat", "rb")

    f = pickle.load(file, encoding="latin1")
    file.close()

    s=svm.LinearSVC()
    #s = GaussianNB()
    data = Preprocessing.getData(f["data"])
    labels = Preprocessing.getLabels(f["labels"])
    # test = Preprocessing.getData(f["data"][20:30])
    # correct = Preprocessing.getestlabels_otabels(f["labels"][20:30])


    for i in range(len(labels)):
        if labels[i]==2 :
            if (twos < 222):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            twos+=1
        elif labels[i]==4:
            if(fours<200):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            fours+=1

print("Training data : ",len(data_ot))
print("Testing Data : ",len(test_ot))
print("Ones : ",ones," Twos : ",twos," Threes : ",threes," Fours : ",fours)
s.fit(np.array(data_ot), np.array(labels_ot))

c =0
for k in range(len(test_ot)):
    pr = s.predict(np.array(test_ot[k]))
    print("Predicted: ", pr[0], " ,Correct Value: ", testlabels_ot[k] )
    if pr[0] == testlabels_ot[k]:
        c+=1
print(c, "Correct out of ", len(testlabels_ot)," Percesion: " ,c/len(testlabels_ot)*100 )