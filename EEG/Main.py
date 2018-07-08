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

def getRates(videos,lengths):
	sampling_rates = []
	for i, video in enumerate(videos):
		video_length = lengths[i]
		
		sampling_rate = int(len(video[0]) // video_length)
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


deap_reader = Reader.DeapReader()
deap_data, deap_labels = deap_reader.read(start = 29, end = 32)

print(deap_data.shape, deap_labels.shape)



processed_data, processed_labels = [], []

for i, subject in enumerate(deap_data):
	processed_data.append(Preprocessing.processReadings(subject, 128, 63, 40))
	processed_labels.append(Preprocessing.processLabels(deap_labels[i]))


processed_data, processed_labels = np.asarray(processed_data), np.asarray(processed_labels)
# print(processed_data.shape, processed_labels.shape)
pickle.dump(processed_data, open("saved_data_truncated", "wb"))
pickle.dump(processed_labels, open("saved_labels_truncated", "wb"))


processed_data = pickle.load(open("saved_data_truncated", "rb"))
processed_labels = pickle.load(open("saved_labels_truncated", "rb"))


print("loaded data", len(processed_data), len(processed_data[0]), len(processed_data[0][0]) )
print("loaded labels", len(processed_labels), len(processed_labels[0]), (processed_labels[0][0]))

with open("Results.txt", "a") as f:
	import CLFs

	iterations = 10
	for subject_i, subject in enumerate(processed_data):
		try:
			total_results = None
			for i in range(iterations):
				s = np.arange(processed_data.shape[1])
				np.random.shuffle(s)
				subject_labels = np.asarray(processed_labels[subject_i])
				# print(manual_labels)
				# print(manual_labels[s])

				# print("-------------------------------- Single Class CLF ------------------------------------")
				clf = CLFs.SingleClass(np.asarray(processed_data[subject_i][s]), np.asarray(subject_labels[s]) )
				clf.train(True)

				iteration_results = clf.predict()
				# print("Iteration res", iteration_results)
				if not total_results is None:
					total_results += iteration_results
				else:
					total_results = iteration_results


				# print("-------------------------------- Multi Class CLF ------------------------------------")
				# clf = CLFs.MultiClass(flat_deap, np.asarray(flat_deap_labels))
				# clf.train(1)
				# clf.predict(aa_data, aa_labels)

			total_results/= iterations
			print(total_results)
			f.write("-------\n")
			for res in total_results:
				f.write(str(res)+" ")
			f.write("\n")
		except:
			print("Bad Subject")
			continue
