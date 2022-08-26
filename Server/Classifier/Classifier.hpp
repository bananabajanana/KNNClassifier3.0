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
    const int k;
    std::vector<Item> classified;
    std::vector<Item> unClassified;
    std::vector<Item> kindOfClassified;
    /**
     * set a classified items.
     * @param classified - the classified items.
     */
    void setClassified(const std::vector<Item>& classified);
    /**
    * set a unclassified items.
    * @param unClassified - the unclassified items.
    */
    void setUnclassified(const std::vector<Item>& unClassified);
    /**
    * Helps the "defItem" function algorithm finding the closest iris
    * and sending its place - while changing the distance to max value.
    * @param distances - vector of distances.
    * @return the place of the closest point.
    */
    static int whereMinInArr(std::vector<double>& distances);

public:
    /**
    * Define an undefined flower.
    * @param item - The flower.
    * @param typeDis - The distance method we are going to use.
     */
    void defItem(Item& item, DistanceCalc& typeDis) const;

    /**
     * Defines all the unclassified items.
     * @param unclassified - all the unclassified items.
     * @param typeDis - whe distance method we use.
     */
    void defItems(std::vector<Item>& unclassified, DistanceCalc& typeDis) const;

    /**
     * Creat classifier for merging unclassified.
     * @param k - the amount of items that we are using.
     */
    Classifier(int k);
};

#endif