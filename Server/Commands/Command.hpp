#ifndef KNNCLASSIFIER3_0_COMMAND_HPP
#define KNNCLASSIFIER3_0_COMMAND_HPP

#include "Server/IOServices/DefaultIO.hpp"
#include "Server/Classifier/Classifier.hpp"
#include <string>

class Command {
private:
    std::string description;
protected:
    DefaultIO *dio;
    Classifier &classifier;
public:
    Command(Classifier &classifier, DefaultIO *dio, std::string description);
    virtual void execute() = 0;
    std::string getDescription();
};


#endif //KNNCLASSIFIER3_0_COMMAND_HPP
