#!usr/bin/python
import numpy as np
import sys
import Reader
import Preprocessing
import pickle
from sklearn.preprocessing import RobustScaler
import math


deap_reader = Reader.DeapReader()
deap_data, deap_labels = deap_reader.read([1])
aa_reader = Reader.AaReader()
# aa_data, aa_labels = aa_reader.read([["NOUR_ABDELAAL_REC_0.csv", "NOUR_ABDELAAL_REC_1.csv",
# 							 "NOUR_ABDELAAL_REC_2.csv", "NOUR_ABDELAAL_REC_3.csv"]], ["NOUR_ABDELAAL_LABELS1.dat"])


aa_data, aa_labels = aa_reader.read([["OSAKA_REC0.csv", "OSAKA_REC1.csv",
							 "OSAKA_REC2.csv", "OSAKA_REC3.csv"]], ["OSAKA_LABELS.dat"])
aa_data = Preprocessing.car_filter(aa_data)
aa_data = Preprocessing.decimate_signal(aa_data)
#aa_data = decimate_signal(aa_data, dsType='IIR')

# #data, labels = reader.read([["NOUR_ABDELAAL_REC_0.csv", "NOUR_ABDELAAL_REC_1.csv",
# # 							 "NOUR_ABDELAAL_REC_2.csv", "NOUR_ABDELAAL_REC_3.csv"],
# # 							 ["OSAKA_REC0.csv", "OSAKA_REC1.csv",
# # 							 "OSAKA_REC2.csv", "OSAKA_REC3.csv"]], ["NOUR_ABDELAAL_LABELS1.dat", "OSAKA_LABELS.dat"])

sampling_rates = [128 for _ in deap_data ]
sampling_rates.append(271)
sampling_rates.append(206)

video_lengths = [63 for _ in deap_data]
video_lengths.append(4 * 60)
video_lengths.append(4 * 60)


channel_nos = [40 for _ in deap_data]
channel_nos.append(14)
channel_nos.append(14)


print("deap data shape", deap_data.shape)
print("deap labels shape", deap_labels.shape)

print("aa data shape", aa_data.shape)
print("aa labels shape", aa_labels.shape)
processed_data, processed_labels = [], []


data = deap_data.tolist() + aa_data.tolist()
labels = deap_labels.tolist() + aa_labels.tolist()

print("raw labels", len(labels), len(labels[0]), len(labels[0][0]))
for i, subject in enumerate(data):
	processed_data.append(Preprocessing.processReadings(subject, sampling_rates[i], video_lengths[i], channel_nos[i]))
	processed_labels.append(Preprocessing.processLabels(labels[i]))


processed_data, processed_labels = np.asarray(processed_data), np.asarray(processed_labels)
pickle.dump(processed_data, open("saved_data", "wb"))
pickle.dump(processed_labels, open("saved_labels", "wb"))

deap_data = [1]
processed_data = pickle.load(open("saved_data", "rb"))
processed_labels = pickle.load(open("saved_labels", "rb"))


print("loaded data", len(processed_data), len(processed_data[0]), len(processed_data[0][0]) )
print("loaded labels", len(processed_labels), len(processed_labels[0]), (processed_labels[0][0]))

import CLFs
processed_deap_data = processed_data[:len(deap_data)]
processed_deap_labels = processed_labels[:len(deap_data)]

flat_deap = [ video  for subject in processed_deap_data for video in subject]
flat_deap_labels = [label for videolabels in processed_deap_labels for label in videolabels]

aa_data = processed_data[-1]
aa_labels = processed_labels[-1]


print("flat deap",len(flat_deap), len(flat_deap[0]), len(flat_deap_labels), (flat_deap_labels[0]))
print("flat aa", len(aa_data), len(aa_labels))

print("-------------------------------- Single Class CLF ------------------------------------")
clf = CLFs.SingleClass(flat_deap, np.asarray(flat_deap_labels))
clf.train(False)
clf.predict(aa_data, aa_labels)


print("-------------------------------- Multi Class CLF ------------------------------------")
clf = CLFs.MultiClass(flat_deap, np.asarray(flat_deap_labels))
clf.train(1)
clf.predict(aa_data, aa_labels)

