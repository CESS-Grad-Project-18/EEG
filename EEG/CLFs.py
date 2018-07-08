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
							sklearn.svm.SVC( degree=1),
							sklearn.svm.SVC( ),


							sklearn.naive_bayes.MultinomialNB(),
							sklearn.naive_bayes.GaussianNB(),
							sklearn.naive_bayes.BernoulliNB(),
							
							sklearn.ensemble.RandomForestClassifier(),
							sklearn.ensemble.AdaBoostClassifier(learning_rate=0.4),
							sklearn.ensemble.RandomForestClassifier(random_state=1),
							sklearn.ensemble.AdaBoostClassifier(learning_rate=0.5),

							sklearn.neighbors.KNeighborsClassifier(),
							# sklearn.neural_network.MLPClassifier(),

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

	def divideData(self, features, labels, percentage):
		thv = 0
		tlv = 0
		tha = 0
		tla = 0
		ctotal = 0
		carousal = 0
		cvalence = 0
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
		for i in range(len(labels)):
			if (labels[i]==1 or labels[i]==4):
				if (ha < countha * percentage):
					arousaldata_ot.append(features[i])
					arousallabels_ot.append(1)
					##print(1)
				else:
					arousaltest_ot.append(features[i])
					arousaltestlabels_ot.append(1)
					##print(1)
				ha+=1
			elif (labels[i]==2 or labels[i]==3):
				if(la< countla * percentage):
					arousaldata_ot.append(features[i])
					arousallabels_ot.append(0)
					##print(0)
				else:
					arousaltest_ot.append(features[i])
					arousaltestlabels_ot.append(0)
					##print(0)
				la+=1

		for i in range(len(labels)):
			if labels[i]==1 or labels[i]==2:
				if (hv < counthv * percentage):
					valencedata_ot.append(features[i])
					valencelabels_ot.append(1)
					##print(1)
				else:
					valencetest_ot.append(features[i])
					valencetestlabels_ot.append(1)
					##print(1)
				hv+=1
			elif labels[i]==3 or labels[i]==4:
				
				if(lv< countlv * percentage):
					valencedata_ot.append(features[i])
					valencelabels_ot.append(0)
					##print(0)
				else:
					valencetest_ot.append(features[i])
					valencetestlabels_ot.append(0)
					##print(0)
				lv+=1

		return	valencedata_ot, valencelabels_ot, valencetest_ot, valencetestlabels_ot, arousaldata_ot, arousallabels_ot, arousaltest_ot, arousaltestlabels_ot

	def train(self, percentage = 0.75):
		self.valencedata_ot, self.valencelabels_ot, self.valencetest_ot, self.valencetestlabels_ot, self.arousaldata_ot, self.arousallabels_ot, self.arousaltest_ot, self.arousaltestlabels_ot = \
		self.divideData(self.features, self.labels, percentage)

		print("lengths = ", len(self.arousaldata_ot), len(self.arousaltest_ot), len(self.valencedata_ot), len(self.valencetest_ot))	
		print("Total = ", len(self.arousaldata_ot) + len(self.arousaltest_ot) + len(self.valencedata_ot) + len(self.valencetest_ot))	
		print("Arousal train shape", len(self.arousaldata_ot) )
		self._arousal_clfs = deepcopy(self.list_of_clfs)
		self._valence_clfs = deepcopy(self.list_of_clfs)
		for i in range(len(self._arousal_clfs)):
			self._arousal_clfs[i].fit(np.array(self.arousaldata_ot), np.array(self.arousallabels_ot))
			self._valence_clfs[i].fit(np.array(self.valencedata_ot), np.array(self.valencelabels_ot))


	def predict(self, features_test = None, features_labels = None):
		if( features_test != None):
			_, _, self.valencetest_ot, self.valencetestlabels_ot, _, _, self.arousaltest_ot, self.arousaltestlabels_ot = \
			self.divideData(features_test, features_labels, 0)


		highest_perc_a, highest_clf_a, highest_perc_v, highest_clf_v = 0, None, 0, None
		for a_clf, v_clf in zip(self._arousal_clfs, self._valence_clfs):
			print("Clf name:", a_clf, v_clf)

			c_a, c_v = 0.0, 0.0
			pr_a_list = a_clf.predict(np.array(self.arousaltest_ot))
			pr_v_list = v_clf.predict(np.array(self.valencetest_ot))

			for pr_a, pr_v, label_a, label_v  in zip(pr_a_list, pr_v_list, 
													self.arousallabels_ot, self.valencelabels_ot):
				print("pred a:", pr_a, " correct:", label_a)
				print("pred v:", pr_v, " correct:", label_v)

				if pr_a == label_a:
					c_a+=1
				if pr_v == label_v:
					c_v += 1

			perc_a =  c_a / len(self.arousaltest_ot)
			perc_v = c_v / len(self.valencetest_ot)

			print(c_a, "Correct out of ", 
		  		len(pr_a_list),
			  	" Percesion: " ,
			  	perc_a * 100 )
			print(c_v, "Correct out of ", 
		  		len(pr_v_list),
			  	" Percesion: " ,
			  	perc_v * 100 )

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

	def train(self, split = True):
		self.features = np.asarray(self.features)
		self.labels = np.asarray(self.labels)
		# print("features_shape:", self.features.shape)
		# print("labels_shape:", self.labels.shape)

		# print("Trainning labels", self.labels)

		label_filter = [1,3]

		modified_features, modified_labels = [], []
		for d,l in zip(self.features, self.labels):
			if l in label_filter:
				modified_features.append(d)
				modified_labels.append(l)
		self.features, self.labels = modified_features, modified_labels

		if split:
				training_to_test_p = 0.75
		else:
				training_to_test_p = 1
		
		training_len = int(training_to_test_p * len(self.features))

		# print("Number of training example:", training_len)
		features_train = np.asarray( self.features[:training_len] )
		labels_train   = np.asarray( self.labels[:training_len] )

		self.features_test = self.features[training_len:]
		self.labels_test =   self.labels[training_len:]


		# print("Trainning with", features_train.shape)
		# print("labeling with", labels_train.shape)
		for clf in self.list_of_clfs:
			# print("Clf name:", clf)
			# print(features_train.shape, labels_train.shape)
			clf.fit(features_train, labels_train)


	def predict(self, features_test = None, labels_test = None):
		clfs_acc = [0 for _ in self.list_of_clfs]
		if features_test != None:
			self.features_test = features_test
			self.labels_test = labels_test
		self.features_test = np.asarray(self.features_test)
		self.labels_test = np.asarray(self.labels_test)
		# print("predicting with", "features", self.features_test.shape, "labels", self.labels_test.shape )
		highest_acc, highest_clf = 0, None
		for clf_i, clf in enumerate(self.list_of_clfs):
			# print("Clf name:", clf)
			c = 0
			for prediction, actual_label in zip(clf.predict(self.features_test), self.labels_test):
				# print("Predicted: ", prediction, " ,Correct Value: ", actual_label )
				if(prediction == actual_label):
					c+=1

			accuracy = c/len(self.labels_test)
			# print(c, "Correct out of ", 
		  		# len(self.labels_test),
			  	# " Percesion: " ,
			  	# accuracy * 100 )

			clfs_acc[clf_i] += accuracy

			if(accuracy >= highest_acc):
				highest_acc = accuracy
				highest_clf = clf
		# print("\n\n")
		# print("Highest accuracy:", highest_acc * 100,
			  # "Highest Clf:", highest_clf)
		# print("_____________________________________")

		return np.asarray(clfs_acc)