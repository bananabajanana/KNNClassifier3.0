#ifndef KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP
#define KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP

#include "Server/Commands/Command.cpp"

class SettingsCommand : public Command {
public:
    SettingsCommand(Classifier &classifier, DefaultIO *dio);
    void execute() override;
};


#endif //KNNCLASSIFIER3_0_SETTINGSCOMMAND_HPP
