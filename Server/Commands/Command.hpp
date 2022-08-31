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
    /**
     * Create command.
     * @param classifier - the "black box" which has a lot of data that can help us for applying the mission.
     * @param dio - the format which we send our answers.
     * @param description - the description of the mission.
     */
    Command(Classifier &classifier, DefaultIO *dio, std::string description);

    /**
     * Runs a specific command.
     */
    virtual void execute() = 0;

    /**
     * the description of the mission.
     * @return description.
     */
    std::string getDescription();
};


#endif //KNNCLASSIFIER3_0_COMMAND_HPP
