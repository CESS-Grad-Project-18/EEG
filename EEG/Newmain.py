#!usr/bin/python
import numpy as np
from Reader import read
import Preprocessing
import clfs

data, labels = read(start = 1, end = 32)
processed_data, processed_labels = [], []

for i, subject in enumerate(data):
	processed_data.append(Preprocessing.processReadings(subject))
	processed_labels.append(Preprocessing.processLabels(labels[i]))

# for start_index in range(0,len(data),40):
# 	processed_data.append( Preprocessing.processReadings(data[start_index: start_index + 40]) )
# 	processed_labels.append( Preprocessing.processLabels(labels[start_index: start_index + 40]) )

processed_data, processed_labels = np.array(processed_data), np.array(processed_labels)

for i in range(len(processed_data)):
	clfs.main(processed_data[i], processed_labels[i])
