//
// Created by Kassem Bagher on 2019-04-15.
//

#include <iostream>
#include "SOM.h"


void SOM::trainData(std::vector<std::vector<double>> &inputData, std::vector<std::vector<double>> weights) {

    // init data
    initData(inputData, weights);

    /**
     * For each epoch, the following steps are involved: </br>
     * 1- get the next input vector node </br>
     * 2- find the smallest distance between the node and the output nodes </br>
     * 3- update the winner node weight edge </br>
     * 4- repeat for all input data for the current epoch </br>
     * 5- repeat previous steps for the remaining epochs </br>
     */
    for (int currentEpoch = 0; currentEpoch < epochs; currentEpoch++) {
        /**
         * 1- Loop through all input data
         */
        for (int inputIndex = 0; inputIndex < inputSize; inputIndex++) {
            /**
             * 2- find the smallest distance between the current input vector
             * and the output nodes
             */
            int sDistanceIndex = smallestDistance(dataArray[inputIndex][0], dataArray[inputIndex][1]);
            /**
             * 3- update the winner node edge weight
             */
            ;
            double distance = neighborhoodSize *
                              (1.0 - ((double) currentEpoch / (double) epochs));

            std::list<int> neighboursList;
            if (neighborhoodSize > 0)
                SOM::getNodeNeighbours(sDistanceIndex, distance, neighboursList);

            updateWinnerClusterNode(sDistanceIndex, inputIndex, currentEpoch + 1);
            if (neighborhoodSize > 0) {
                for (int x : neighboursList) {
                    updateNeighbours(sDistanceIndex, x, currentEpoch + 1);
                }
            }
        }
        // 4- go to the next input vector
    } // 5- go to the next epoch if there are any epochs remaining
}

int SOM::getCluster(std::vector<double> &inputVector) {
    return smallestDistance(inputVector[0], inputVector[1]);
}

int SOM::smallestDistance(double &x, double &y) {
    /**
     * smallest distance index in the weight matrix
     * used temporary in searching for smallest value
     * and returned to the caller.
     */
    int smallestDistanceIndex = INT_MIN;
    double smallestDistance = DBL_MAX;

    double distance = 0;

    for (int weightIndex = 0; weightIndex < weightsSize; weightIndex++) {
        distance = pointsDistance(x, y, weightsArray[weightIndex][0], weightsArray[weightIndex][1]);
        // keep tracking of the smallest distance found
        if (distance < smallestDistance) {
            smallestDistance = distance;
            smallestDistanceIndex = weightIndex;
        }
    }
    return smallestDistanceIndex;
}

void
SOM::updateNeighbours(int winnerNodeIndex, int neighbourIndex, int epoch) {
    double training = (learningRate / epoch);

    for (unsigned y = 0; y < 2; y++) {

        double distance = weightsArray[winnerNodeIndex][y] - weightsArray[neighbourIndex][y];

        double neighborFactor = exp(-((epoch - 1) * (epoch - 1)) / (2 * neighborhoodSize * neighborhoodSize));
        neighborFactor = neighborFactor * neighborhoodSize;
        double neighbour = exp(-(distance * distance) / (neighborFactor * neighborFactor));
        weightsArray[neighbourIndex][y] = weightsArray[neighbourIndex][y] + (training * neighbour * distance);
    }
}

void SOM::updateWinnerClusterNode(int clusterNodeIndex, int inputIndex, double epoch) {
    // TODO: check constants operations
    double training = (learningRate / epoch);
    for (int i = 0; i < 2; i++) {
        double distance = dataArray[inputIndex][i] - weightsArray[clusterNodeIndex][i];
        weightsArray[clusterNodeIndex][i] = weightsArray[clusterNodeIndex][i] + ((training * distance));
    }
}

double SOM::pointsDistance(double &x1, double &y1, double &x2, double &y2) {
    double distance = 0.0;
    distance += pow(x1 - x2, 2);
    distance += pow(y1 - y2, 2);
    distance = sqrt(distance);
    return distance;
}

void SOM::getNodeNeighbours(int &winnerIndex, double &distance, std::list<int> &list) {

    for (unsigned x = 0; x < weightsSize; x++) {
        if (x == winnerIndex) continue;

        if (SOM::pointsDistance(weightsArray[x][0],
                                weightsArray[x][1],
                                weightsArray[winnerIndex][0],
                                weightsArray[winnerIndex][1]) <= distance) {
            list.push_back(x);
        }
    }
}


std::vector<std::vector<double>> SOM::getWeights() {

    // copy weights array into the weights vector
    if (weights.size() == 0) {
        weights.clear();
        for (int x = 0; x < weightsSize; ++x) {
            weights.push_back({weightsArray[x][0], weightsArray[x][1]});
        }
    }
    return weights;
}

void SOM::initData(std::vector<std::vector<double>> &inputData, std::vector<std::vector<double>> &weights) {

    inputSize = inputData.size();
    weightsSize = weights.size();
    dataArray = new double[inputSize][2];
    weightsArray = new double[weightsSize][2];

    // copy the weight vector into a 2D double array
    for (unsigned x = 0; x < weightsSize; x++) {
        weightsArray[x][0] = weights[x][0];
        weightsArray[x][1] = weights[x][1];
    }

    // copy the data vector into a 2D double array
    for (unsigned x = 0; x < inputSize; x++) {
        dataArray[x][0] = inputData[x][0];
        dataArray[x][1] = inputData[x][1];
    }
}

SOM::~SOM() {
    delete[] dataArray;
};


SOM::SOM(int epochs, double neighborhoodSize, double learningRate) : epochs(epochs),
                                                                     neighborhoodSize(
                                                                             neighborhoodSize),
                                                                     learningRate(learningRate) {
    if (learningRate > 1 || learningRate <= 0)
        throw "Learning rate should be <=1 and >0";
    if (epochs <= 0)
        throw "Epochs should be > 0";
}

