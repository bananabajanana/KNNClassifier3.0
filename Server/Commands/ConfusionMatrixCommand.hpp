#ifndef KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
#define KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP

#include "Server/Commands/Command.cpp"

class ConfusionMatrixCommand : public Command{
public:
    ConfusionMatrixCommand(Classifier &classifier, DefaultIO *dio);
};


#endif //KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
