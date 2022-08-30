#ifndef FLOWER_H_DEFINITION
#define FLOWER_H_DEFINITION
#include "Server/Classifier/NPoints.hpp"

/**
 * Item object - type of item + its Properties.
 */
class Item {
private:
    std::string type;
     NPoint character;

public:

    /**
     * Set type of the item.
     * @param typeItem  - the type;
     */
    void setType(std::string typeItem);

    /**
     * Get the NPoint in the coordinate system.
     * @return the NPoint.
     */
    const NPoint getPoint() const;

    /**
     * Get the NPoint in the type of the item.
     * @return the type.
     */
    std::string getTypeOfItem() const;

     /**
      * Creat the flower using its characteristics that has a type.
      * @param properties - the item's properties.
      * @param n - number of properties.
      * @param type - the item's type.
      */
    Item(double* properties,int n, std::string type);

    /**
    * Creat the flower using its characteristics with no type.
    * @param properties - the item's properties.
    * @param n - number of properties.
    */
    Item(double* properties,int n);
    Item(std::vector<double> properties, std::string type);
    Item(std::vector<double> properties);
    void pushProperty(double property);
};

#endif