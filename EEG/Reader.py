import sys
import numpy as np
import pickle
import time

def read(list_of_files = [1,14,17], start = None, end = None):
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
	return data,labels
if __name__ == "__main__":
	
	data, labels = read(start = 1, end = 32)
	
	
 

