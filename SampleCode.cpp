
#include <iostream>
#include "SOM.h"

using namespace std;

void printPoints(vector<vector<double>> &weights) {
    for (int i = 0; i < weights.size(); ++i) {
        cout << weights[i][0] << "," << weights[i][1] << endl;
    }
}

int main() {

    // training data
    vector<vector<double>> data = {
            {2,2},
            {5,5},
            {2,1},
            {1,2},
            {6,5},
            {5,6},
            {10,4},
            {11,3},
            {9,2},
            {6,7}
    };

    // initial weights
    vector<vector<double>> weights = {
            {1, 3},
            {6, 4},
            {10, 1}
    };

    // print the adjusted weights
    cout << "Initial weights (x,y)" << endl;
    printPoints(weights);

    // Create a new SOM object and set the parameters
    SOM som = SOM::builder()
            .setEpochs(100) // number if iterations > 0
            .setLearningRate(1) // learning rate <= 1 and > 0
            .setNeighborhoodSize(0) // neighborhood function size
            .build();


    // train the network using the provided training data and initial weights
    clock_t tStart = clock(); // track training time
    som.trainData(data, weights);
    double time = (double) (clock() - tStart) / CLOCKS_PER_SEC;


    // get the adjusted weights and print them
    vector<vector<double>> adjusted = som.getWeights();
    cout << "\nAdjusted weights (x,y)" << endl;
    printPoints(adjusted);


    // Print points and their clusters
    cout << "\nPoints clusters" << endl;
    for (int i = 0; i < data.size(); ++i) {
        int clusterIndex = som.getCluster(data[i]);
        cout << data[i][0] << "," << data[i][1] << " belongs to cluster " <<
             adjusted[clusterIndex][0] << "," << adjusted[clusterIndex][1] << endl;
    }

    // print training time
    printf("\nTime taken: %.2fs\n", time);

}
