#ifndef KNNCLASSIFIER3_0_CLASSIFYCOMMAND_HPP
#define KNNCLASSIFIER3_0_CLASSIFYCOMMAND_HPP

#include "Server/Commands/Command.hpp"

class ClassifyCommand : public Command {
public:
    /**
     * Constructor.
     */
    ClassifyCommand(Classifier &classifier, DefaultIO *dio);

    void execute() override;
};


#endif //KNNCLASSIFIER3_0_CLASSIFYCOMMAND_HPP
