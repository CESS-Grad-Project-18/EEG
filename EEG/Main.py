#!usr/bin/python
import numpy as np
import sys
import Reader
import Preprocessing
import pickle
from sklearn.preprocessing import RobustScaler
import math
import os
import sys

def getRates(videos):
	sampling_rates = []
	for i, video in enumerate(videos):
		if( i < happy_vids ):
			video_length = 3 * 60
		else:
			video_length = 5 * 50
		
		sampling_rate = len(video[0]) // video_length
		sampling_rates.append(sampling_rate)
	return sampling_rates
def truncateSamples(videos, sampling_rates):
	diffs = []
	for i, video in enumerate(videos):
		if( i < happy_vids ):
			video_length = 3 * 60
		else:
			video_length = 5 * 50

		perfect = sampling_rates[i] * video_length
		diffs.append(len(video[0]) - perfect)

		for ch, channel in enumerate(video):
			videos[i][ch] = videos[i][ch][:perfect]
	print(diffs)

happy_vids, sad_vids = 14, 18
# aa_reader = Reader.AaReader()
# happyfiles = ["Happy/"+filename for filename in os.listdir("./Happy")]
# sadfiles = ["Sad/"+filename for filename in os.listdir("./Sad")]
# files = happyfiles + sadfiles
# aa_data, aa_labels = aa_reader.read([files], ["Attia_Labels_1.1.dat"])


# aa_data = Preprocessing.car_filter(aa_data)
# aa_data = Preprocessing.decimate_signal(aa_data)
# print("--- Printing ---")

#aa_data = decimate_signal(aa_data, dsType='IIR')
# sampling_rates = getRates(aa_data[0])
# print(sampling_rates)
# truncateSamples(aa_data[0], sampling_rates)
# # sys.exit()
#
# video_lengths = []
# for _ in happyfiles:
# 	video_lengths.append(3 * 60)
# for _ in sadfiles:
# 	video_lengths.append(5 * 60)
#
#
# channel_nos = [14 for _ in files]
#
#
# processed_data, processed_labels = [], []
#
# aa_data = aa_data.tolist()
# aa_data[0].pop( (happy_vids + 3) - 1)
#
# aa_labels = aa_labels.tolist()
# aa_labels[0].pop((happy_vids + 3) - 1)
#
# aa_data, aa_labels = np.asarray(aa_data), np.asarray(aa_labels)
#
# print("aa data shape", aa_data.shape)
# print("aa labels shape", aa_labels.shape)
#
# for i, subject in enumerate(aa_data):
# 	processed_data.append(Preprocessing.processReadings(subject, sampling_rates[i], video_lengths[i], channel_nos[i]))
# 	processed_labels.append(Preprocessing.processLabels(aa_labels[i]))
#
#
# processed_data, processed_labels = np.asarray(processed_data), np.asarray(processed_labels)
# print(processed_data.shape, processed_labels.shape)
# pickle.dump(processed_data, open("saved_data_truncated", "wb"))
# pickle.dump(processed_labels, open("saved_labels_truncated", "wb"))


processed_data_aa = pickle.load(open("saved_data_truncated_aa", "rb"))
processed_labels_aa = pickle.load(open("saved_labels_truncated_aa", "rb"))


print("loaded data", len(processed_data_aa), len(processed_data_aa[0]), len(processed_data_aa[0][0]) )
print("loaded labels", len(processed_labels_aa), len(processed_labels_aa[0]), (processed_labels_aa[0][0]))


processed_data_on = pickle.load(open("saved_data_truncated_on", "rb"))
processed_labels_on = pickle.load(open("saved_labels_truncated_on", "rb"))


print("loaded data", len(processed_data_on), len(processed_data_on[0]), len(processed_data_on[0][0]) )
print("loaded labels", len(processed_labels_on), len(processed_labels_on[0]), (processed_labels_on[0][0]))
# manual_labels = [1 if i < happy_vids else 3 for i in range(happy_vids + sad_vids - 1) ]
m_l_aa = [1 for _ in range(14)]
for _ in range(17):
	m_l_aa.append(3)

m_l_on = [1 for _ in range(10)]
for _ in range(9):
	m_l_on.append(3)

processed_data = np.concatenate([processed_data_aa[0], processed_data_on[0]])
manual_labels = m_l_aa + m_l_on

print("Total shape", processed_data.shape)
print("Total labels", len(manual_labels))
import CLFs
s = np.arange(processed_data.shape[1])
np.random.shuffle(s)
manual_labels = np.asarray(manual_labels)
print(manual_labels)
print(manual_labels[s])
# print("-------------------------------- Single Class CLF ------------------------------------")
clf = CLFs.SingleClass(np.asarray(processed_data[0][s]), np.asarray(manual_labels[s]) )
clf.train(True)
clf.predict()


# print("-------------------------------- Multi Class CLF ------------------------------------")
# clf = CLFs.MultiClass(flat_deap, np.asarray(flat_deap_labels))
# clf.train(1)
# clf.predict(aa_data, aa_labels)

