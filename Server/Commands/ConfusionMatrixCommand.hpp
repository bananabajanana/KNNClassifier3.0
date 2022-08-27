#ifndef KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
#define KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP

#include "Server/Commands/Command.cpp"
#include "Server/Commands/SettingsCommand.hpp"

class ConfusionMatrixCommand : public Command{
private:
    static int findPosInVector(const std::vector<std::string> v, const Item& item);
public:
    ConfusionMatrixCommand(Classifier &classifier, DefaultIO *dio);
    void execute() override;

    void printConfusionMatrix(DefaultIO *dio, int size, int[size];
};


#endif //KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
