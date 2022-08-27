#ifndef KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP
#define KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP

#include "Server/Commands/Command.cpp"
#include "Server/Classifier/srcDistances/distCalculators/EuclideanDistance.hpp"
#include "Server/Classifier/srcDistances/distCalculators/ChebyshevDistance.hpp"
#include "Server/Classifier/srcDistances/distCalculators/ManhattanDistance.hpp"
#include <cstring>

class SettingsCommand : public Command {
public:
    static std::string stringSettings(Classifier &classifier);
    SettingsCommand(Classifier &classifier, DefaultIO *dio);
    void execute() override;
};


#endif //KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP
