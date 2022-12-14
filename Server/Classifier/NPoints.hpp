#ifndef FOURD_POINT_H_DEFINITION
#define FOURD_POINT_H_DEFINITION
#include <iostream>
#include <vector>
/**
 * Point with N dimensions in the coordinate system.
 */
class NPoint {
private:
     std::vector<double> Point;
public:
    NPoint(std::vector<double>& properties);
    /**
     * Returns the point.
     * @return  point.
     */
    std::vector<double> getPoint() const;

    /**
     * Returns the number of dimensions.
     * @return N.
     */
    int getN() const;

    /**
     * Creates a point in the coordinate system using the properties.
     * @param properties
     * @param n
     */
    NPoint(double* properties, int n);

    /**
     * Get array of N properties and makes from that a point that is a vector.
     * @param properties - the properties of a point.
     * @param n - the number of dimensions.
     * @return the point as vector.
     */
    static std::vector<double> makePoint(double* properties, int n);
    void pushProperty(double property);
};

#endif