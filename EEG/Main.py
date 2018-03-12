import numpy as np
import Preprocessing
# import Plotter
import pickle
# from sklearn import svm
# from sklearn.naive_bayes import GaussianNB
# import matplotlib.pyplot as plt
# import warnings
from sklearn.preprocessing import RobustScaler
import math
# from mlxtend.plotting import plot_decision_regions
# warnings.filterwarnings("ignore")

data_ot = []
labels_ot = []

ones=0
twos=0
threes=0
fours=0
for i in range(1,2):
    if i<10:
        file = open("./"+"s0"+str(i)+".dat", "rb")
    else:
        file = open("./s" +str(i) + ".dat", "rb")

    f = pickle.load(file, encoding="latin1")
    file.close()

    # s=svm.LinearSVC()
    #s = GaussianNB()
    data = Preprocessing.getData(f["data"])
    labels = Preprocessing.getLabels(f["labels"])


    label_filter = [1,3]
    for d, label in zip(data,labels):
    	if label in label_filter:
    		data_ot.append(d)
    		labels_ot.append(label)
    # we train with 75% of the data and test with the rest
    features = data_ot
    labels = labels_ot
    # features = np.asarray(data_ot[: int(0.75 * len(data_ot))])
    # labels = np.asarray(labels_ot[: len(features)])

    # testing_features = np.asarray( data_ot[len(features):])
    # testing_labels = np.asarray( labels_ot[len(features):])

    # ones = len( np.where(np.asarray(labels_ot) == 1)[0] )
    # threes = len(labels_ot) - ones


# print("Training data : ",len(features), len(labels))
# print("Testing Data : ",len(testing_features), len(testing_labels))
# print("Total : ", ones + threes)
# print("Ones : ",ones," Twos : ",twos," Threes : ",threes," Fours : ",fours)
# print("Ones in training data : ", len(np.where(labels == 1)[0])  )
# print("Threes in training data : ", len(np.where(testing_labels == 3)[0])  )

# s.fit(features, labels)


# c = 0
# for prediction, actual_label in zip(s.predict(testing_features), testing_labels):
# 	print("Predicted: ", prediction, " ,Correct Value: ", actual_label )
# 	if(prediction == actual_label):
# 		c+=1
# print(c, "Correct out of ", len(testing_labels)," Percesion: " ,c/len(testing_labels)*100 )


import ./Classifier/WIPClfs

clf = WIPClfs.MultiClass()