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
    void setType(const std::string &typeItem);

    /**
     * Get the NPoint in the coordinate system.
     * @return the NPoint.
     */
    NPoint getPoint() const;

    /**
     * Get the NPoint in the type of the item.
     * @return the type.
     */
    std::string getTypeOfItem() const;

     /**
      * Constructor
      * @param properties - the item's properties
      * @param n - number of properties
      * @param type - the item's type
      */
    Item(double* properties,int n, const std::string& type);

    /**
     * Constructor
     * @param properties item's properties
     * @param n properties array length
     */
    Item(double* properties,int n);

    /**
     * Constructor
     * @param properties item's properties
     * @param type item's type
     */
    Item(const std::vector<double>& properties, const std::string& type);

    /**
     * Constructor
     * @param properties item's properties
     */
    Item(const std::vector<double>& properties);

    /**
     * Adds a single property at the end of the item's properties vector.
     * @param property property to add
     */
    void pushProperty(double property);
};

#endif