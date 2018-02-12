import numpy as np
import Preprocessing
import Classifiers
import Plotter
import pickle
from sklearn import svm
from sklearn.naive_bayes import GaussianNB
import matplotlib.pyplot as plt
import warnings
from sklearn.preprocessing import RobustScaler
from sklearn.preprocessing import StandardScaler
import math
import sklearn
warnings.filterwarnings("ignore")

t1 = 0
t2 = 0
t3 = 0
t4 = 0
percentage = 0.75

for i in range(1,6):
    ones=0
    twos=0
    threes=0
    fours=0
    countones=0
    counttwos=0
    countthrees=0
    countfours=0
    data_ot = []
    labels_ot = []
    test_ot=[]
    testlabels_ot=[]
    if i<10:
        file = open("C:/Users/HP/Downloads/data_preprocessed_python/data_preprocessed_python/s0"+str(i)+".dat", "rb")
    else:
        file = open("C:/Users/HP/Downloads/data_preprocessed_python/data_preprocessed_python/s" +str(i) + ".dat", "rb")

    f = pickle.load(file, encoding="latin1")
    file.close()
    print("\n ///////////////////////\n")
    if i<10:
        print("File s0" + str(i) + "\n")
    else:
        print("File s" + str(i) + "\n")
    data = Preprocessing.getData(f["data"])
    labels = Preprocessing.getLabels(f["labels"])
    data = StandardScaler().fit_transform(data)

    for i in range(len(labels)):
        if labels[i]==1:
            countones+=1
            t1+=1
        if labels[i]==2:
            counttwos+=1
            t2+=1
        if labels[i]==3:
            countthrees+=1
            t3+=1
        if labels[i]==4:
            countfours+=1
            t4+=1
    #s = GaussianNB()

    for i in range(len(labels)):
        if labels[i]==1:
            if (ones < countones * percentage):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            ones+=1
        elif labels[i]==2:
            if(twos< counttwos * percentage):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            twos+=1
        elif labels[i]==3:
            if(threes< countthrees * percentage):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            threes+=1
        elif labels[i]==4:
            if(fours< countfours * percentage):
                data_ot.append(data[i])
                labels_ot.append(labels[i])
            else:
                test_ot.append(data[i])
                testlabels_ot.append(labels[i])
            fours+=1

    print("Training data : ",len(data_ot))
    print("Testing Data : ",len(test_ot))
    print("Ones : ",ones," Twos : ",twos," Threes : ",threes," Fours : ",fours)

    Classifiers.SVM(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,False)
    Classifiers.NB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,False)
    Classifiers.VotingClassifier(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,False)
    Classifiers.Adaboost(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,False)


    #print("Training data : ",len(data_ot))
    #print("Testing Data : ",len(test_ot))
    #print("Ones : ",ones," Twos : ",twos," Threes : ",threes," Fours : ",fours)
    ##print(test_ot[0])
    #s=svm.LinearSVC()
    #s.fit(np.array(data_ot), np.array(labels_ot))

    #c =0
    #for k in range(len(test_ot)):
    #    pr = s.predict(np.array([test_ot[k]]))
    #    print("Predicted: ", pr[0], " ,Correct Value: ", testlabels_ot[k] )
    #    if pr[0] == testlabels_ot[k]:
    #        c+=1
    #print(c, "Correct out of ", len(testlabels_ot)," Percesion: " ,c/len(testlabels_ot)*100 )

print("\n\n///////////////////////////////////////\n\n")
print("Total numbers : Ones : ",t1," Twos : ",t2," Threes : ",t3," Fours : ",t4)