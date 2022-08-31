#ifndef KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
#define KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP

#include "Server/Commands/SettingsCommand.hpp"


class ConfusionMatrixCommand : public Command{
private:
    /**
     * Helper function that finds a position of an item's type in a vector.
     * @param v vector to search in
     * @param item item of which type we want to search
     * @return the position of the type in the vector
     */
    static int findPosInVector(const std::vector<std::string>& v, const Item& item);

public:
    /**
     * Constructor
     */
    ConfusionMatrixCommand(Classifier &classifier, DefaultIO *dio);

    void execute() override;
};


#endif //KNNCLASSIFIER3_0_CONFUSIONMATRIXCOMMAND_HPP
