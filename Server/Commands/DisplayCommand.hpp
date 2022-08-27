#ifndef KNNCLASSIFIER3_0_DISPLAYCOMMAND_HPP
#define KNNCLASSIFIER3_0_DISPLAYCOMMAND_HPP

#include "Server/Commands/Command.cpp"

class DisplayCommand : public Command {
public:
    DisplayCommand(Classifier &classifier, DefaultIO *dio);
    void execute() override;
};


#endif //KNNCLASSIFIER3_0_DISPLAYCOMMAND_HPP
