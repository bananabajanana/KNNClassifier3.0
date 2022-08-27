#ifndef KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
#define KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP

#include "Server/Commands/Command.cpp"
#include "Server/Commands/SettingsCommand.hpp"

class ConfusionMatrixCommand : public Command{
private:
    /**
     * Helper function that finds a position of an item's type in a vector.
     * !!!!MICHAL!!!!
     *      There probably is an existing function for this that i didn't find...
     *      please help...
     * @param v
     * @param item
     * @return
     */
    static int findPosInVector(const std::vector<std::string> v, const Item& item);
public:
    /**
     * Constructor
     */
    ConfusionMatrixCommand(Classifier &classifier, DefaultIO *dio);
    void execute() override;
};


#endif //KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
