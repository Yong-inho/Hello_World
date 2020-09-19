class knn:
	k = 0 #The k of k-NN
	num_of_data = 0 #The number of data
	label = []
	x = []
	y = []

	#Reading data from csv file
	def read_csv_input(self, path):
		f = open(path, "r")
		f.readline()

		while True:
			temp_line = f.readline()
	
			if len(temp_line) == 0:
				break
			else:
				temp_label, temp_x, temp_y = temp_line.split(',')
				temp_y = temp_y[:-1]
	
				self.label.append(temp_label)
				self.x.append(temp_x)
				self.y.append(temp_y)
		
				self.num_of_data += 1
		f.close()

	#Setting k
	def set_k(self, k):
		self.k = k
	
	#Predicting the label to given input
	def expected_label(self, x, y):
		distance = [] 
		label = self.label
		sum_of_label = 0
		
		#When calculating the distance, sqrt is not used since we don't need exact distance
		for i in range(self.num_of_data):
			distance.append((float(self.x[i]) - x) ** 2 + (float(self.y[i]) - y) ** 2)

		#Sorting distances and labels with respect to distance
		for i in range(self.num_of_data):
			for j in range(self.num_of_data-1):
				if distance[j] > distance[j+1]:
					temp_distance, temp_label = distance[j], label[j]
					distance[j], label[j] = distance[j+1], label[j+1]
					distance[j+1], label[j+1] = temp_distance, temp_label
		
		#extracting k-nearest neighbor
		for i in range(self.k):
			sum_of_label += int(label[i])

			
		#If there are more 1s than 0s, sum of label will be greater than k/2 
		if sum_of_label > self.k/2:
			print('expected label for [{}, {}]: 1'.format(x, y))
		else:
			print('expected label for [{}, {}]: 0'.format(x, y))

test_x = [1.4, 1.4, 0.9, -0.1, 2.5]
test_y = [0.2, 0.5, 4.0, 3.0, 0.1]

model = knn()
model.read_csv_input('KNN.csv')
model.set_k(int(input("1. K=3, 2. K=5 -> ")))

for i in range(len(test_x)):
	model.expected_label(test_x[i], test_y[i])

