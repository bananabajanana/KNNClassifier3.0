#ifndef KNNCLASSIFIER3_0_COMMAND_HPP
#define KNNCLASSIFIER3_0_COMMAND_HPP

#include "Server/IOServices/DefaultIO.hpp"
#include <string>

class Command {
private:
    std::string description;
    DefaultIO *dio;
public:
    virtual void execute() = 0;
};


#endif //KNNCLASSIFIER3_0_COMMAND_HPP
