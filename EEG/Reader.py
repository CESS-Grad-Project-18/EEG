import sys
import numpy as np
import pickle
import time
from abc import ABC, abstractmethod

class Reader(ABC):

	@abstractmethod
	def read(self):
		pass

class DeapReader(Reader):
	# @override
	def read(self, list_of_files = [1,14,17], start = None, end = None):
		labels = []
		data = []

		if start != None:
			files = range(start, end+1)
		else:
			files = list_of_files
		tik = time.time()
		for i in files:
			if i<10:
				file = open("./"+"s0"+str(i)+".dat", "rb")
			else:
				file = open("./s" +str(i) + ".dat", "rb")

			f = pickle.load(file, encoding="latin1")
			file.close()
			data.append( f["data"] )
			labels.append( f["labels"] )
		tok = time.time()
		print(len(data), sys.getsizeof(data))
		# data,labels  = np.array(data), np.array(labels)
		print("Read (",len(list(files)),") file(s) in:",tok - tik, "s")
		# print("Data read:",data.shape, "Labels:", labels.shape)
		return np.asarray(data),np.asarray(labels)


class AaReader(Reader): #Aa ahmed attia's Reader

	# @override
	def read(self, dfn, lfn): #list of data file names, list of labels file name
		"""
		Expected that for a single label file, we would have list of video files
		EX:
		label files = [ [ [1,2], [3,4], [5,6] ], [ [7,8], [9,10], [11,12], [13,14] ] ]
		this means we have 2 subjects, first subject has 3 video files.
		each file has a label of valence and arousal.

		the second subject has 4 video files.
		"""

		no_channels = 14
		labels = []
		data = []

		tik = time.time()
		for label_index, label_file in enumerate(lfn):

			with open("./" + label_file) as f:
				local_videos_labels = [ list(map(float, line.split(",") )) for line in f.readlines() ]

				subject_data, subject_labels = [], []
				for data_file_index, data_file in enumerate(dfn[label_index]):
					with open("./" + data_file) as f:
						local_video_channels = [ [] for _ in range(no_channels)] # create Initial 14 channels
						lines = f.readlines()

						for line in lines[1:]: # first line is a header line
							if(line == "\n"):
								continue
							for channel_no, channel_value in enumerate( map(int, line.split(", ")[2:16] ) ): # we need channel 2 to 14
								local_video_channels[channel_no].append(channel_value)
					
						subject_data.append(local_video_channels)
						subject_labels.append(local_videos_labels[data_file_index])


				data.append(subject_data)
				labels.append(subject_labels)

		tok = time.time()
		print("Read: ", len(data), " file(s) in:", tok - tik, "s")	

		return np.asarray(data), np.asarray(labels)



if __name__ == "__main__":
	
	data, labels = read(start = 1, end = 32)
	
	
 

