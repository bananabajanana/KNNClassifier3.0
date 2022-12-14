#ifndef CLASSIFIER_H_INCLUDED
#define CLASSIFIER_H_INCLUDED

#include <iostream>
#include <vector>
#include <cmath>
#include "Server/Classifier/Item.hpp"
#include "Server/Classifier/srcDistances/DistanceCalc.hpp"
#include "Server/Classifier/srcDistances/distCalculators/EuclideanDistance.hpp"

#define MAX_NUM 1.7976931348623157E+308

/**
 * Classifier defines flowers with the knn algorithm.
 */
class Classifier {
private:
    //region Server params
    int k;
    bool wasTestClassified;
    std::vector<Item> originalTrainingData;
    std::vector<Item> outputTestData;
    std::vector<Item> classifiedTrainingData;
    DistanceCalc *dist;
    //endregion

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
    bool isThereTestData();

    /**
    * if there is trainingData items.
    * @return true or false trainingData items that were declared.
    */
    bool isThereTrainingData();

    /**
     * Defines all the unclassified items.
     * @param unclassified - all the unclassified items.
     * @param typeDis - whe distance method we use.
     */
    void defItems();

    void defTrainingData();

    /**
     * Setter for the Distance Type
     * @param dist - distance calculator
     */
    void setDistanceType(DistanceCalc *dist);

    /**
     * @return Distance calculator
     */
    DistanceCalc *getDistanceType();

    /**
     * Setter for the K value
     * @param k - new K
     */
    void setK(int& k);

    /**
     * @return K value
     */
    int getK();

    /**
     * @return the Classified Test Data vector
     */
    const std::vector<Item>& getTestOutputData();

    /**
     * @return the Given Test Data (with user-given types)
     */
    const std::vector<Item>& getClassifiedTrainingData();

    /**
     * @return the Training Data.
     */
    const std::vector<Item>& getOriginalTrainingData();

    /**
     * Creat classifier for merging unclassified.
     * @param k - the amount of items that we are using.
     */
    Classifier(int k);

    /**
     * @return Whether the last given test data was classified by the classifier.
     */
    bool wasClassified() const;

    /**
     * @param items a vector of items with different types
     * @return a vector of the different types.
     */
    static void addTypes(const std::vector<Item> &items, std::vector<std::string> &output);

    ~Classifier();
};

#endif