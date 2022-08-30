#include "Server/Classifier/NPoints.hpp"

NPoint::NPoint(double* properties, int n)
        : Point(makePoint(properties, n))
{
}

NPoint::NPoint(std::vector<double> properties)
        : Point(properties)
{
}

const std::vector<double> NPoint::getPoint() const {
    return Point;
}

std::vector<double> NPoint::makePoint(double* properties, int n) {
    std::vector<double> temp;
    for(int i=0;i<n;i++) {
        temp.push_back(properties[i]);
    }
    return temp;
}

const int NPoint::getN() const{
    return Point.size();
}
void NPoint::pushProperty(double property) {
    Point.push_back(property);
}