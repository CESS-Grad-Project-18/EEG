#!usr/bin/python
import numpy as np
from Reader import read
import Preprocessing
import clfs

data, labels = read()
processed_data, processed_labels = [], []

for i, subject in enumerate(data):
	processed_data.append(Preprocessing.processReadings(subject))
	processed_labels.append(Preprocessing.processLabels(labels[i]))


processed_data, processed_labels = np.array(processed_data), np.array(processed_labels)

for i in range(len(processed_data)):
	clfs.main(processed_data[i], processed_labels[i])
