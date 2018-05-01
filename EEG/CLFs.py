from abc import ABC, abstractmethod
from copy import deepcopy
import numpy as np
# from sklearn import *
import sklearn.svm
import sklearn.naive_bayes
import sklearn.ensemble
import sklearn.neighbors
import sklearn.neural_network
import sklearn.tree
class BaseClf(ABC):
	def __init__(self, features, labels):
		self.list_of_clfs = [sklearn.svm.SVC(kernel="poly", degree=1),
							sklearn.svm.LinearSVC(),

							sklearn.naive_bayes.MultinomialNB(),
							sklearn.naive_bayes.GaussianNB(),
							sklearn.naive_bayes.BernoulliNB(),
							
							sklearn.ensemble.RandomForestClassifier(),
							sklearn.ensemble.AdaBoostClassifier(learning_rate=0.4),
							sklearn.ensemble.RandomForestClassifier(random_state=1),
							sklearn.ensemble.AdaBoostClassifier(learning_rate=0.5),

							# sklearn.neighbors.KNeighborsClassifier(),
							sklearn.neural_network.MLPClassifier(),

							sklearn.tree.DecisionTreeClassifier()]

		self.features = features
		self.labels = labels
		super().__init__()

	@abstractmethod
	def train(self):
		pass

	@abstractmethod
	def predict(self):
		pass

class MultiClass(BaseClf):
	def combine(valence,arousal):
		if(valence==0 and arousal == 0):
			return 3
		if(valence==1 and arousal == 0):
			return 2
		if(valence==0 and arousal == 1):
			return 4
		if(valence==1 and arousal == 1):
			return 1


	def train(self):
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

		self.valencedata_ot = []
		self.valencelabels_ot = []
		self.valencetest_ot = []
		self.valencetestlabels_ot = []

		self.arousaldata_ot = []
		self.arousallabels_ot = []
		self.arousaltest_ot = []
		self.arousaltestlabels_ot = []

		for i in range(len(self.labels)):
			if self.labels[i]==1 or self.labels[i]==4:
				countha+=1
				tha+=1
			if self.labels[i]==2 or self.labels[i]==3:
				countla+=1
				tla+=1
			if self.labels[i]==1 or self.labels[i]==2:
				counthv+=1
				thv+=1
			if self.labels[i]==3 or self.labels[i]==4:
				countlv+=1
				tlv+=1
		for i in range(len(self.labels)):
			if (self.labels[i]==1 or self.labels[i]==4):
				if (ha < countha * percentage):
					self.arousaldata_ot.append(self.features[i])
					self.arousallabels_ot.append(1)
					##print(1)
				else:
					self.arousaltest_ot.append(self.features[i])
					self.arousaltestlabels_ot.append(1)
					##print(1)
				ha+=1
			elif (self.labels[i]==2 or self.labels[i]==3):
				if(la< countla * percentage):
					self.arousaldata_ot.append(self.features[i])
					self.arousallabels_ot.append(0)
					##print(0)
				else:
					self.arousaltest_ot.append(self.features[i])
					self.arousaltestlabels_ot.append(0)
					##print(0)
				la+=1

		for i in range(len(self.labels)):
			if self.labels[i]==1 or self.labels[i]==2:
				if (hv < counthv * percentage):
					self.valencedata_ot.append(self.features[i])
					self.valencelabels_ot.append(1)
					##print(1)
				else:
					self.valencetest_ot.append(self.features[i])
					self.valencetestlabels_ot.append(1)
					##print(1)
				hv+=1
			elif self.labels[i]==3 or self.labels[i]==4:
				
				if(lv< countlv * percentage):
					self.valencedata_ot.append(self.features[i])
					self.valencelabels_ot.append(0)
					##print(0)
				else:
					self.valencetest_ot.append(self.features[i])
					self.valencetestlabels_ot.append(0)
					##print(0)
				lv+=1

		print("Arousal train shape", len(self.arousaldata_ot))
		self._arousal_clfs = deepcopy(self.list_of_clfs)
		self._valence_clfs = deepcopy(self.list_of_clfs)
		for i in range(len(self._arousal_clfs)):
			self._arousal_clfs[i].fit(np.array(self.arousaldata_ot), np.array(self.arousallabels_ot))
			self._valence_clfs[i].fit(np.array(self.valencedata_ot), np.array(self.valencelabels_ot))


	def predict(self):
		highest_perc_a, highest_clf_a, highest_perc_v, highest_clf_v = 0, None, 0, None
		for a_clf, v_clf in zip(self._arousal_clfs, self._valence_clfs):
			c_a, c_v = 0.0, 0.0
			pr_a_list = a_clf.predict(np.array(self.arousaltest_ot))
			pr_v_list = v_clf.predict(np.array(self.valencetest_ot))

			for pr_a, pr_v, label_a, label_v  in zip(pr_a_list, pr_v_list, 
													self.arousallabels_ot, self.valencelabels_ot):
				if pr_a == label_a:
					c_a+=1
				if pr_v == label_v:
					c_v += 1
			perc_a =  c_a / len(self.arousaltest_ot)
			perc_v = c_v / len(self.valencetest_ot)

			if(perc_a > highest_perc_a):
				highest_perc_a = perc_a
				highest_clf_a = a_clf
			if(perc_v > highest_perc_v):
				highest_perc_v = perc_v
				highest_clf_v = v_clf

		print("Highest clfs arousal:", highest_clf_a)
		print("Highest clf valence:", highest_clf_v)
		print("arousal:", highest_perc_a*100 )
		print("valence", highest_perc_v*100 )


class SingleClass(BaseClf):

	def train(self):
		print("features_shape:", self.features.shape)
		print("labels_shape:", self.labels.shape)

		label_filter = [1,2,3,4]
		modified_features, modified_labels = [], []
		for d,l in zip(self.features, self.labels):
			if l in label_filter:
				modified_features.append(d)
				modified_labels.append(l)
		self.features, self.labels = modified_features, modified_labels
		highest_acc, highest_clf = 0, None
		training_len = int(0.75 * len(self.features))
		print("Number of training example:", training_len)
		features_train = np.asarray( self.features[:training_len] )
		labels_train   = np.asarray( self.labels[:training_len] )

		self.features_test = self.features[training_len:]
		self.labels_test =   self.labels[training_len:]


		print("Trainning with", features_train.shape)
		print("labeling with", labels_train.shape)
		for clf in self.list_of_clfs:
			# print("Clf name:", clf)
			# print(features_train.shape, labels_train.shape)
			clf.fit(features_train, labels_train)


	def predict(self):
		for clf in self.list_of_clfs:
			# print("Clf name:", clf)
			highest_acc, highest_clf = 0, None
			c = 0
			for prediction, actual_label in zip(clf.predict(self.features_test), self.labels_test):
				# print("Predicted: ", prediction, " ,Correct Value: ", actual_label )
				if(prediction == actual_label):
					c+=1

			accuracy = c/len(self.labels_test)
			# print(c, "Correct out of ", 
		 #  		len(self.labels_test),
			#   	" Percesion: " ,
			#   	accuracy * 100 )
			if(accuracy >= highest_acc):
				highest_acc = accuracy
				highest_clf = clf
		print("\n\n")
		print("Highest accuracy:", highest_acc * 100,
			  "Highest Clf:", highest_clf)
		print("_____________________________________")
