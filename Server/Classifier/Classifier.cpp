#include "Classifier.hpp"
#include <map>
#include <algorithm>

Classifier::Classifier(int k) : k(k) {

}
void Classifier::setUnclassified(const std::vector<Item>& unClassified) {
    this->unClassified.clear();
    this->kindOfClassified.clear();
    for(auto& item:unClassified) {
        this->unClassified.push_back(item);
        this->kindOfClassified.push_back(item);
    }
}

void Classifier::setClassified(const std::vector<Item>& classified) {
    this->classified.clear();
    for(auto& item:classified) {
        this->classified.push_back(item);
    }
}

void Classifier::defItems(std::vector<Item>& unclassified, DistanceCalc& typeDis) const{
    for(int i = 0; i < unclassified.size();i++) {
        defItem(unclassified[i], typeDis);
    }
}
void Classifier::defItem(Item& item, DistanceCalc& typeDis) const{
    std::vector<double> distances;
    std::vector<Item> results;

    for(auto & i : classified) {
        distances.push_back(typeDis.dist(item.getPoint(), i.getPoint()));
    }

    for(int i=0;i<k;i++) {
        results.push_back(classified[whereMinInArr(distances)]);
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