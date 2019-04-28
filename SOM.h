//
// Created by Kassem Bagher on 2019-04-15.
//

#ifndef DISTRIBUTEDSOM_SOM_H
#define DISTRIBUTEDSOM_SOM_H

#include "SOM.h"
#include "cmath"
#include "cfloat"
#include <vector>
#include "list"

class SOM {

    // Constructors and builder
public:

    ~SOM();      // destructor

    SOM(int epochs, double neighborhoodSize, double learningRate);

    class builder;


    // private variables
private:
    int epochs;
    double neighborhoodSize;
    double learningRate;
    std::vector<std::vector<double>> weights;
    size_t weightsSize;
    size_t inputSize;
    double (*weightsArray)[2];
    double (*dataArray)[2];
    // private functions
private:

    /**
     * initialise internal data
     * @param inputData input training data
     * @param weights initial weights (initial map)
     */
    void initData(std::vector<std::vector<double>> &inputData, std::vector<std::vector<double>> &weights);

    /**
     * Find the smallest distance between input vector and all weight nodes
     * @param x input vector x value
     * @param y input vector y value
     * @return the index of the nearest weight vector
     */
    int smallestDistance(double &x, double &y);

    /**
     * Update the winning node's (weight vector) value using the learning rate
     * @param clusterNodeIndex the winner node index in the weights array
     * @param inputIndex the index of the closest input vector to the weight node
     * @param epoch current iteration
     */
    void updateWinnerClusterNode(int clusterNodeIndex, int inputIndex, double epoch);

    /**
     * Update a neighbour node
     * @param winnerNodeIndex the winner node index in the weights array
     * @param neighbourIndex the neighbour node index in the weights array
     * @param epoch current iteration
     */
    void updateNeighbours(int winnerNodeIndex, int neighbourIndex, int epoch);

    /**
     * Returns the neighbours of the given node within
     * a specified distance
     * @param winnerIndex node index
     * @param distance distance to search for
     * @param list neighbours nodes index in the weights array
     */
    void getNodeNeighbours(int &winnerIndex, double &distance, std::list<int> &list);

    /**
     * Calculate the Euclidean distance between two points
     * @param x1 point1 x value
     * @param y1 point1 y value
     * @param x2 point2 x value
     * @param y2 point2 y value
     * @return distance between two points
     */
    double pointsDistance(double &x1, double &y1, double &x2, double &y2);

    // public functions
public:
    int getCluster(std::vector<double> &inputVector);

    std::vector<std::vector<double>> getWeights();

    /**
     * Train input data.
     * @param inputData 2D input data for training
     * @param weights initial weights (initial map)
     */
    void trainData(std::vector<std::vector<double>> &inputData, std::vector<std::vector<double>> weights);
};

class SOM::builder {
public:

    builder &setEpochs(int value) {
        epochs = value;
        return *this;
    };

    builder &setNeighborhoodSize(double value) {
        neighborhoodSize = value;
        return *this;
    };


    builder &setLearningRate(double value) {
        learningRate = value;
        return *this;
    };

    SOM build() const {
        return SOM{epochs, neighborhoodSize, learningRate};
    }

private:
    int epochs;
    double neighborhoodSize = 0;
    double learningRate = 1;
};


#endif //DISTRIBUTEDSOM_SOM_H
