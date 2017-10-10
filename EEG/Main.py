import numpy as np
import Preprocessing
import pickle
from sklearn import svm
from sklearn.naive_bayes import GaussianNB
import matplotestlabels_otib.pyplot as plt
import warnings
from sklearn.preprocessing import RobustScaler
import math
warnings.filterwarnings("ignore")
'''
for i in range(1,32):
    if i<10:
        file = open("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s0"+str(i)+".dat", "rb")
    else:
        file = open("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s" +str(i) + ".dat", "rb")
    f = pickle.load(file, encoding="latin1")
    file.close()
    d=[]
    l=[]
    test=[]
    s=[]
    t=[0,1,2,15,17,18,19,3,14,16,30,31,33,34,8,9,10,11,12,13,27,4,5,6,7,24]
    r=[28,29,32,35,36,37,24,25,26,39,22,20,23]

    for k in t:
        d+=Preprocessing.getData([f["data"][k]])
        l+=Preprocessing.getestlabels_otabels([f["labels"][k]])
    for k in r:
        test += Preprocessing.getData([f["data"][k]])
        s += Preprocessing.getestlabels_otabels([f["labels"][k]])
    clf = GaussianNB()
    clf.fit(np.array(d), np.array(l))
    c =0
    for k in range(len(test)):
        pr = clf.predict(np.array(test[k]))
        #print("Predicted: ", pr[0], " ,Correct Value: ", s[i] )
        if pr[0] == s[k]:
            c+=1
    print(i," : ",c, "Correct out of ", len(test)," Percesion: " ,c/len(test)*100 )'''

for i in range(1,2):
    '''if i<10:
        file = open("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s0"+str(i)+".dat", "rb")
    else:
        file = open("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s" +str(i) + ".dat", "rb")'''
    file = open("D:/Boody/CESS/GP/EEG/data_preprocessed_python/s01.dat", "rb")

    f = pickle.load(file, encoding="latin1")
    file.close()

    s=svm.LinearSVC()
    #s = GaussianNB()
    data = Preprocessing.getData(f["data"][:20]) + Preprocessing.getData(f["data"][30:])
    labels = Preprocessing.getestlabels_otabels(f["labels"][0:20]) + Preprocessing.getestlabels_otabels(f["labels"][30:])
    # test = Preprocessing.getData(f["data"][20:30])
    # correct = Preprocessing.getestlabels_otabels(f["labels"][20:30])

    data_ot = []
    labels_ot = []
    test_ot=[]
    testlabels_ot=[]
    ones=0
    threes=0
    for i in range(len(labels)):
        if labels[i]==1 :
            if (ones < 5):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            ones+=1
        elif labels[i]==3:
            if(threes<5):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            threes+=1
    s.fit(np.array(data_ot), np.array(labels_ot))

    c =0
    for k in range(len(test_ot)):
        pr = s.predict(np.array(test_ot[k]))
        print("Predicted: ", pr[0], " ,Correct Value: ", testlabels_ot[k] )
        if pr[0] == testlabels_ot[k]:
            c+=1
    print(i," : ",c, "Correct out of ", len(testlabels_ot)," Percesion: " ,c/len(testlabels_ot)*100 )