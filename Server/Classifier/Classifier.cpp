#include "Classifier.hpp"
#include <map>
#include <algorithm>

Classifier::Classifier(int k) : k(k), wasTestClassified(false) {
    this->dist = new EuclideanDistance();
}

void Classifier::setTestData(const std::vector<Item>& unClassified) {
    this->outputTestData.clear();
    this->inputTestData.clear();
    for(auto& item:unClassified) {
        this->outputTestData.push_back(item);
        this->inputTestData.push_back(item);
    }
    wasTestClassified = false;
}

void Classifier::setTrainingData(const std::vector<Item>& classified) {
    this->trainingData.clear();
    for(auto& item:classified) {
        this->trainingData.push_back(item);
    }
}

void Classifier::defItems(){
    for(int i = 0; i < outputTestData.size(); i++) {
        defItem(outputTestData[i], *dist);
    }
    wasTestClassified = true;
}

void Classifier::setDistanceType(DistanceCalc *dist) {
    this->dist = dist;
}

DistanceCalc *Classifier::getDistanceType() {
    return dist;
}

void Classifier::setK(int &k) {
    this-> k = k;
}

int Classifier::getK() {
    return k;
}

bool Classifier::isThereTrainingData() {
    return !trainingData.empty();
}

bool Classifier::isThereTestData() {
    return !outputTestData.empty();
}

void Classifier::defItem(Item& item, DistanceCalc& typeDis) {
    std::vector<double> distances;
    std::vector<Item> results;
    for(auto & i : trainingData) {
        distances.push_back(typeDis.dist(item.getPoint(), i.getPoint()));
    }

    for(int i=0;i<k;i++) {
        results.push_back(trainingData[whereMinInArr(distances)]);
    }

    std::map<std::string, double> mapTypes;
    for(int i=0;i<k;i++) {
        if(mapTypes.find(results[i].getTypeOfItem())==mapTypes.end()) {
            mapTypes[results[i].getTypeOfItem()] = 1;
        }
        else {
            mapTypes[results[i].getTypeOfItem()]++;
        }
    }
    auto maxPair = std::max_element(mapTypes.begin(), mapTypes.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });
    item.setType(maxPair->first);
}

int Classifier::whereMinInArr(std::vector<double>& distances) {
    double min = MAX_NUM;
    for(double distance : distances) {
        if(min > distance) {
            min = distance;
        }
    }
    for(int i=0;i<distances.size();i++) {
        if(min == distances[i]) {
            distances[i] = MAX_NUM;
            return i;
        }
    }
    return 0;

}

const std::vector<Item> &Classifier::getTestOutputData() {
    return outputTestData;
}

const std::vector<Item> &Classifier::getTestInputData() {
    return inputTestData;
}

const std::vector<Item> &Classifier::getTrainingData() {
    return trainingData;
}

const bool Classifier::wasClassified() {
    return wasTestClassified;
}

void Classifier::addTypes(const std::vector<Item> &items, std::vector<std::string> &output) {
    for(int i = 0; i < items.size(); i++) {
        if(!std::count(output.begin(), output.end(), items[i].getTypeOfItem())) {
            output.push_back(items[i].getTypeOfItem());
        }
    }
}