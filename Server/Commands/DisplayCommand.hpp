#ifndef KNNCLASSIFIER3_0_DISPLAYCOMMAND_HPP
#define KNNCLASSIFIER3_0_DISPLAYCOMMAND_HPP

#include "Server/Commands/Command.hpp"

class DisplayCommand : public Command {
public:
    /**
     * Constructor
     */
    DisplayCommand(Classifier &classifier, DefaultIO *dio);

    void execute() override;
};


#endif //KNNCLASSIFIER3_0_DISPLAYCOMMAND_HPP
