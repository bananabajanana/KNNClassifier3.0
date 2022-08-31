#include "Server/Classifier/Item.hpp"

void Item::setType(const std::string &typeItem) {
    type = typeItem;
}

std::string Item::getTypeOfItem() const{
    return type;
}

NPoint Item::getPoint() const{
    return character;
}

Item::Item(double* properties, int n, const std::string& type)
        :character(properties, n)
{
    this->type = type;
}

Item::Item(double* properties, int n)
        :character(properties, n)
{
    this->type = "";
}

Item::Item(const std::vector<double>& properties, const std::string& type)
        :character(properties)
{
    this->type = type;
}

Item::Item(const std::vector<double>& properties)
        :character(properties)
{
    this->type = "";
}
void Item::pushProperty(double property)

{
    character.pushProperty(property);
}

Item::~Item() = default;
