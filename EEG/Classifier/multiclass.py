import numpy as np
from sklearn import ensemble
import Preprocessing
import Plotter
import pickle
import sklearn
from sklearn import svm
from sklearn import neighbors
from sklearn.naive_bayes import GaussianNB
from sklearn import preprocessing
import matplotlib.pyplot as plt
import warnings
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import RobustScaler
import math
from sklearn import neural_network
import random

warnings.filterwarnings("ignore")

def combine(valence,arousal):
    if(valence==0 and arousal == 0):
        return 3
    if(valence==1 and arousal == 0):
        return 2
    if(valence==0 and arousal == 1):
        return 4
    if(valence==1 and arousal == 1):
        return 1

thv = 0
tlv = 0
tha = 0
tla = 0
ctotal = 0
carousal = 0
cvalence = 0
percentage = 0.75
num=0
hv=0
lv=0
ha=0
la=0

counthv=0
countlv=0
countha=0
countla=0

valencedata_ot = []
valencelabels_ot = []
valencetest_ot = []
valencetestlabels_ot = []

arousaldata_ot = []
arousallabels_ot = []
arousaltest_ot = []
arousaltestlabels_ot = []
for i in range(1,33):
    
    
    if i<10:
        file = open("C:/Users/HP/Downloads/data_preprocessed_python/data_preprocessed_python/s0"+str(i)+".dat", "rb")
    else:
        file = open("C:/Users/HP/Downloads/data_preprocessed_python/data_preprocessed_python/s" +str(i) + ".dat", "rb")

    f = pickle.load(file, encoding="latin1")
    file.close()
    if i<10:
        print("Processing File s0" + str(i) + "\n")
    else:
        print("Processing File s" + str(i) + "\n")


    data = Preprocessing.getData(f["data"])
    min_max_scaler = preprocessing.MinMaxScaler()
    data = min_max_scaler.fit_transform(data)
    labels = Preprocessing.getLabels(f["labels"])
    #z = StandardScaler()
    #data = z.fit_transform(data)
    #data = z.fit_transform(data)
    ##########################################
    shuffler = list(zip(data,labels))
    random.shuffle(shuffler)
    data, labels = zip(*shuffler)
    ##########################################
    for i in range(len(labels)):
        if labels[i]==1 or labels[i]==4:
            countha+=1
            tha+=1
        if labels[i]==2 or labels[i]==3:
            countla+=1
            tla+=1
        if labels[i]==1 or labels[i]==2:
            counthv+=1
            thv+=1
        if labels[i]==3 or labels[i]==4:
            countlv+=1
            tlv+=1

    #s = GaussianNB()
    ##print("\n\n///////////////////////////////////////////")

    #for i in range(len(labels)):
    #    #print(labels[i])

    ##print("///////////////////////////////////////////\n\n")

    for i in range(len(labels)):
        if (labels[i]==1 or labels[i]==4):
            if (ha < countha * percentage):
                arousaldata_ot.append(data[i])
                arousallabels_ot.append(1)
                ##print(1)
            else:
                arousaltest_ot.append(data[i])
                arousaltestlabels_ot.append(1)
                ##print(1)
            ha+=1
        elif (labels[i]==2 or labels[i]==3):
            if(la< countla * percentage):
                arousaldata_ot.append(data[i])
                arousallabels_ot.append(0)
                ##print(0)
            else:
                arousaltest_ot.append(data[i])
                arousaltestlabels_ot.append(0)
                ##print(0)
            la+=1
    for i in range(len(labels)):
        if labels[i]==1 or labels[i]==2:
            if (hv < counthv * percentage):
                valencedata_ot.append(data[i])
                valencelabels_ot.append(1)
                ##print(1)
            else:
                valencetest_ot.append(data[i])
                valencetestlabels_ot.append(1)
                ##print(1)
            hv+=1
        elif labels[i]==3 or labels[i]==4:
            
            if(lv< countlv * percentage):
                valencedata_ot.append(data[i])
                valencelabels_ot.append(0)
                ##print(0)
            else:
                valencetest_ot.append(data[i])
                valencetestlabels_ot.append(0)
                ##print(0)
            lv+=1

    """######################################
    shuffler = list(zip(arousaldata_ot,arousallabels_ot))
    random.shuffle(shuffler)
    arousaldata_ot, arousallabels_ot = zip(*shuffler)

    shuffler = list(zip(arousaltest_ot,arousaltestlabels_ot))
    random.shuffle(shuffler)
    arousaltest_ot,arousaltestlabels_ot = zip(*shuffler)

    shuffler = list(zip(valencedata_ot,valencelabels_ot))
    random.shuffle(shuffler)
    valencedata_ot,valencelabels_ot = zip(*shuffler)

    shuffler = list(zip(valencetest_ot,valencetestlabels_ot))
    random.shuffle(shuffler)
    valencetest_ot,valencetestlabels_ot = zip(*shuffler)
    ######################################"""




print("USING SVC")
print("\n//////////////////////////////AROUSAL/////////////////////////////////\n")
#print("Training data : ",len(arousaldata_ot))
#print("Testing Data : ",len(arousaltest_ot))
#print("High Arousal : ",ha," Low arousal : ",la)
##print(test_ot[0])



s1 = sklearn.svm.SVC(kernel="poly", degree=1)
#s1=sklearn.naive_bayes.MultinomialNB()
#s1=sklearn.tree.DecisionTreeClassifier()
#s1=sklearn.ensemble.RandomForestClassifier()
#s1 = neighbors.KNeighborsClassifier()
#s1=ensemble.AdaBoostClassifier(learning_rate=0.5)
#s1 = neural_network.MLPClassifier()





s1.fit(np.array(arousaldata_ot), np.array(arousallabels_ot))

c =0
for k in range(len(arousaltest_ot)):
    pr = s1.predict(np.array([arousaltest_ot[k]]))
    #print("Predicted: ", pr[0], " ,Correct Value: ", arousaltestlabels_ot[k] )
    if pr[0] == arousaltestlabels_ot[k]:
        c+=1
print(c, "Correct out of ", len(arousaltestlabels_ot)," Percesion: " ,c/len(arousaltestlabels_ot)*100 )
carousal += c/len(arousaltestlabels_ot)*100

print("\n//////////////////////////////VALENCE/////////////////////////////////\n")
#print("Training data : ",len(valencedata_ot))
#print("Testing Data : ",len(valencetest_ot))
#print("High Valence : ",hv," Low arousal : ",lv)





s2 = sklearn.svm.SVC(kernel="poly", degree=1)
#s2 = sklearn.naive_bayes.GaussianNB()
#s2 = sklearn.tree.DecisionTreeClassifier()
#s2 = sklearn.ensemble.RandomForestClassifier()
#s2 = ensemble.AdaBoostClassifier(learning_rate=0.5)
#s2 = neighbors.KNeighborsClassifier()
#s2 = neural_network.MLPClassifier()




s2.fit(np.array(valencedata_ot), np.array(valencelabels_ot))

c =0
for k in range(len(valencetest_ot)):
    pr = s1.predict(np.array([valencetest_ot[k]]))
    #print("Predicted: ", pr[0], " ,Correct Value: ", valencetestlabels_ot[k] )
    if pr[0] == valencetestlabels_ot[k]:
        c+=1
print(c, "Correct out of ", len(valencetestlabels_ot)," Percesion: " ,c/len(valencetestlabels_ot)*100 )
cvalence += c/len(valencetestlabels_ot)*100


"""
print("\n//////////////////////////COMBINING BOTH CLASSIFIERS////////////////////////////\n")
r = min(len(valencetest_ot),len(arousaltest_ot))
finaldata = data[-r:]
finallabels = labels[-r:]
c=0 
for k in range(r):
    arousalp = s1.predict(np.array([finaldata[k]]))
    valencep = s2.predict(np.array([finaldata[k]]))
    pr = combine(valencep[0],arousalp[0])
    ##print("Predicted: ", pr, " ,Correct Value: ", finallabels[k] )
    if pr == finallabels[k]:
        c+=1
print(c, "Correct out of ", r," Percesion: " ,(c/r) * 100 )
ctotal += (c/r) * 100
num+=1
"""

