#include "Server/Classifier/Item.hpp"

void Item::setType(std::string typeItem) {
    type = typeItem;
}
std::string Item::getTypeOfItem() const{
    return type;
}
const NPoint Item::getPoint() const{
    return character;
}

Item::Item(double* properties,int n, std::string type)
        :character(properties, n)
{
    this->type = type;
}

Item::Item(double* properties,int n)
        :character(properties, n)
{
    this->type = "";
}