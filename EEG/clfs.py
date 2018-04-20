from sklearn import svm
from sklearn.naive_bayes import GaussianNB
from sklearn.preprocessing import RobustScaler
import numpy as np

def clfsGenerator():
	clfs = [svm.SVC(), 
			svm.SVR(),
			svm.SVC(kernel = "rbf"),
			svm.SVC(C=1.0, tol=1e-10, cache_size=600, kernel='rbf', gamma = 1e-6),
			svm.SVC(C=1.0, tol=1e-10, cache_size=600, kernel='poly', gamma = 1e-6, degree = 70),
			svm.SVC(kernel = "poly"),
			GaussianNB(),
			svm.LinearSVC()]
	for clf in clfs:
		yield clf

def main(features, labels ):
	label_filter = [1,3]
	modified_features, modified_labels = [], []
	for d,l in zip(features, labels):
		if l in label_filter:
			modified_features.append(d)
			modified_labels.append(l)
	features, labels = modified_features, modified_labels
	highest_acc, highest_clf = 0, None
	training_len = int(0.75 * len(features))
	print("Number of training example:", training_len)
	features_train = features[:training_len]
	labels_train   = labels[:training_len]

	features_test = features[training_len:]
	labels_test =   labels[training_len:]

	clf_gen = clfsGenerator()
	for clf in clf_gen:
		print("Clf name:", clf)
		# print(features_train.shape, labels_train.shape)
		clf.fit(features_train, labels_train)
		c = 0
		for prediction, actual_label in zip(clf.predict(features_test), labels_test):
			print("Predicted: ", prediction, " ,Correct Value: ", actual_label )
			if(prediction == actual_label):
				c+=1
		accuracy = c/len(labels_test)
		print(c, "Correct out of ", 
			  len(labels_test),
			  " Percesion: " ,
			  accuracy * 100 )
		if(accuracy >= highest_acc):
			highest_acc = accuracy
			highest_clf = clf
		print("\n\n")
	print("Highest accuracy:", highest_acc * 100,
		  "Highest Clf:", highest_clf)
	print("_____________________________________")

