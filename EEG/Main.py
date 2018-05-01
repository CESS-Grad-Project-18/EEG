#!usr/bin/python
import numpy as np
import sys
import Reader
import Preprocessing
import pickle
from sklearn.preprocessing import RobustScaler
import math


# reader = Reader.DeapReader()
# data, labels = reader.read(start = 1, end = 10)
reader = Reader.AaReader()
data, labels = reader.read([["NOUR_ABDELAAL_REC_0.csv", "NOUR_ABDELAAL_REC_1.csv",
							 "NOUR_ABDELAAL_REC_2.csv", "NOUR_ABDELAAL_REC_3.csv"]], ["NOUR_ABDELAAL_LABELS1.dat"])
# data, labels = reader.read([["NOUR_ABDELAAL_REC_0.csv", "NOUR_ABDELAAL_REC_1.csv",
# 							 "NOUR_ABDELAAL_REC_2.csv", "NOUR_ABDELAAL_REC_3.csv"],
# 							 ["OSAKA_REC0.csv", "OSAKA_REC1.csv",
# 							 "OSAKA_REC2.csv", "OSAKA_REC3.csv"]], ["NOUR_ABDELAAL_LABELS1.dat", "OSAKA_LABELS.dat"])
sampling_rates = [271,266]



print(data.shape)
print(labels.shape)

processed_data, processed_labels = [], []

ones=0
twos=0
threes=0
fours=0


for i, subject in enumerate(data):
	processed_data.append(Preprocessing.processReadings(subject, sampling_rates[i], 4 * 60, 14))

	# processed_data.append(Preprocessing.processReadings(subject, 271, 4 * 60, 14))
	# processed_data.append(Preprocessing.processReadings(subject, 128, 63, 40))

	processed_labels.append(Preprocessing.processLabels(labels[i]))

processed_data, processed_labels = np.asarray(processed_data), np.asarray(processed_labels)

import CLFs
# processed_data = np.concatenate([ processed_data[0], processed_data[1] ])
# processed_labels = np.concatenate([processed_labels[0], processed_labels[1] ] )
print("PD:",processed_data.shape)
print("PL:", processed_labels.shape)

for subject_data, subject_label in zip(processed_data, processed_labels):
	print("-------------------------------aaa----------------------")
	clf = CLFs.SingleClass(subject_data, subject_label)
	clf.train()
	clf.predict()

# clf = CLFs.SingleClass(processed_data, processed_labels)
# clf.train()
# clf.predict()

