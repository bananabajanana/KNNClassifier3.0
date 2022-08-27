#ifndef KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP
#define KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP

#include "Server/Commands/Command.cpp"
#include "Server/Classifier/srcDistances/distCalculators/EuclideanDistance.hpp"
#include "Server/Classifier/srcDistances/distCalculators/ChebyshevDistance.hpp"
#include "Server/Classifier/srcDistances/distCalculators/ManhattanDistance.hpp"
#include <cstring>

class SettingsCommand : public Command {
public:
    /**
     * Constructor.
     */
    SettingsCommand(Classifier &classifier, DefaultIO *dio);

    /**
     * Returns a string representation of the current classifier settings
     * @param classifier classifier.
     * @return representation of settings.
     */
    static std::string stringSettings(Classifier &classifier);

    void execute() override;
};


#endif //KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP
