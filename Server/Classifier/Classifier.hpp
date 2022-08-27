#ifndef CLASSIFIER_H_INCLUDED
#define CLASSIFIER_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#include "Server/Classifier/Item.hpp"
#include "Server/Classifier/srcDistances/DistanceCalc.hpp"

#define MAX_NUM 1.7976931348623157E+308

/**
 * Classifier defines flowers with the knn algorithm.
 */
class Classifier {
private:
    int k;
    std::vector<Item> trainingData;
    std::vector<Item> outputTestData;
    std::vector<Item> inputTestData;
    DistanceCalc *dist;

    /**
    * Helps the "defItem" function algorithm finding the closest iris
    * and sending its place - while changing the distance to max value.
    * @param distances - vector of distances.
    * @return the place of the closest point.
    */
    static int whereMinInArr(std::vector<double>& distances);

    /**
    * Define an undefined flower.
    * @param item - The flower.
    * @param typeDis - The distance method we are going to use.
    */
    void defItem(Item& item, DistanceCalc& typeDis);
public:
    /**
    * set a trainingData items.
    * @param classified - the trainingData items.
    */
    void setTrainingData(const std::vector<Item>& classified);
    /**
    * set a unclassified items.
    * @param unClassified - the unclassified items.
    */
    void setTestData(const std::vector<Item>& unClassified);
    /**
     * if there is Unclassified items.
     * @return true or false Unclassified items that were declared.
     */
    bool isThereUnclassifiedItems();
    /**
    * if there is trainingData items.
    * @return true or false trainingData items that were declared.
    */
    bool isThereClassifiedItems();


    /**
     * Defines all the unclassified items.
     * @param unclassified - all the unclassified items.
     * @param typeDis - whe distance method we use.
     */
    void defItems();

    void setDistanceType(DistanceCalc *dist);

    DistanceCalc *getDistanceType();

    void setK(int& k);

    int getK();

    const std::vector<Item>& getTestOutputData();
    const std::vector<Item>& getTestInputData();
    const std::vector<Item>& getTrainingData();

    /**
     * Creat classifier for merging unclassified.
     * @param k - the amount of items that we are using.
     */
    Classifier(int k);
};

#endif