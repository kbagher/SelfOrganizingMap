# SelfOrganizingMap
Implementation of Kohonen Self-organizing map using 2D training data in C++

![alt text](https://raw.githubusercontent.com/kbagher/SelfOrganizingMap/master/before_after.png)

### Sample Code
Create a 2D double vector containing the network training data
```c++
vector<vector<double>> data = {
	{2,2}, {5,5}, {2,1},
	{1,2}, {6,5}, {5,6},
	{10,4}, {11,3}, {9,2},
	{6,7}
};
```
Create a 2D double vector containing the initial weights (initial map)
```c++
vector<vector<double>> weights = {
	{1, 3}, {6, 4}, {10, 1}
};
```
Create a new SOM object and set the network paramaters
```c++
SOM som = SOM::builder()
	.setEpochs(100) // number if iterations > 0
	.setLearningRate(1) // learning rate <= 1 and > 0
	.setNeighborhoodSize(0) // neighborhood function size
	.build();
```
Train the network using the created training data and the initial weights (initial map)
```c++
som.trainData(data, weights);
```
Call ``` getWeights()``` to return the adjusted weights after the network training is completed
```c++
vector<vector<double>> adjusted = som.getWeights();
```
To get a point’s cluster, call ```getCluster()``` which will return the cluster’s index in the adjusted weights vector
```c++
int clusterIndex = som.getCluster(data[i]);
```

