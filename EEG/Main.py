import numpy as np
import Preprocessing
import Plotter
import pickle
from sklearn import svm
from sklearn.naive_bayes import GaussianNB
import matplotlib.pyplot as plt
import warnings
from sklearn.preprocessing import RobustScaler
import math
# from mlxtend.plotting import plot_decision_regions

warnings.filterwarnings("ignore")

data_ot = []
labels_ot = []

ones=0
twos=0
threes=0
fours=0

first_file_index = 1
last_file_index =  1
print("Using",last_file_index - first_file_index + 1, "file(s)")
# for i in range(first_file_index, last_file_index + 1):
for i in [1]:
    if i<10:
        file = open("./"+"s0"+str(i)+".dat", "rb")
    else:
        file = open("./s" +str(i) + ".dat", "rb")

    f = pickle.load(file, encoding="latin1")
    file.close()

    data = Preprocessing.getData(f["data"])
    labels = Preprocessing.getLabels(f["labels"])


    label_filter = [1,2,3,4]
    for d, label in zip(data,labels):
    	if label in label_filter:
    		data_ot.append(d)
    		labels_ot.append(label)

# from sklearn.decomposition import PCA
# pca = PCA()
# data_ot = pca.fit_transform(data_ot)

# we train with 75% of the data and test with the rest
features = np.asarray(data_ot[: int(0.75 * len(data_ot))])
labels = np.asarray(labels_ot[: len(features)])

testing_features = np.asarray( data_ot[len(features):])
testing_labels = np.asarray( labels_ot[len(features):])

ones = len( np.where(np.asarray(labels_ot) == 1)[0] )
twos = len( np.where(np.asarray(labels_ot) == 2)[0] )
threes = len( np.where(np.asarray(labels_ot) == 3)[0] )
fours = len( np.where(np.asarray(labels_ot) == 4)[0] )
# threes = len(labels_ot) - ones


print("Training data : ",len(features), len(labels))
print("Testing Data : ",len(testing_features), len(testing_labels))
print("Total : ", ones + threes)
print("Ones : ",ones," Twos : ",twos," Threes : ",threes," Fours : ",fours)
print("Ones in training data : ", len(np.where(labels == 1)[0])  )
print("Twos in training data : ", len(np.where(labels == 2)[0])  )
print("Threes in training data : ", len(np.where(labels == 3)[0])  )
print("fours in training data : ", len(np.where(labels == 4)[0])  )

print("Ones in testing data : ", len(np.where(testing_labels == 1)[0])  )
print("Twos in testing data : ", len(np.where(testing_labels == 2)[0])  )
print("Threes in testing data : ", len(np.where(testing_labels == 3)[0])  )
print("fours in testing data : ", len(np.where(testing_labels == 4)[0])  )

clfs = [svm.SVC(), 
        svm.SVR(),
        svm.SVC(kernel = "rbf"),
		svm.SVC(C=1.0, tol=1e-10, cache_size=600, kernel='rbf', gamma = 1e-6),
		svm.SVC(C=1.0, tol=1e-10, cache_size=600, kernel='poly', gamma = 1e-6, degree = 70),
		svm.SVC(kernel = "poly"),
		GaussianNB(),
		svm.LinearSVC()]


for s in clfs:
	print("_____")
	print(s)
    # s=svm.LinearSVC()
    # s = svm.SVC()
    # s = svm.SVR()
    # s = svm.SVC(kernel = "rbf", class_weight = {1:0.15})
    # s = svm.SVC(C=1.0, tol=1e-10, cache_size=600, kernel='rbf', gamma = 1e-6)
    # s = svm.SVC(C=1.0, tol=1e-10, cache_size=600, kernel='poly', gamma = 1e-6)
    # s = svm.SVC(kernel = "poly") 
    # s = GaussianNB()

	s.fit(features, labels)


	c = 0
	for prediction, actual_label in zip(s.predict(testing_features), testing_labels):
		print("Predicted: ", prediction, " ,Correct Value: ", actual_label )
		if(prediction == actual_label):
			c+=1
	print(c, "Correct out of ", len(testing_labels)," Percesion: " ,c/len(testing_labels)*100 )
