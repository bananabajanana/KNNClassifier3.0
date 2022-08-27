#include "ConfusionMatrixCommand.hpp"


ConfusionMatrixCommand::ConfusionMatrixCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "display algorithm confusion matrix") {
}
void ConfusionMatrixCommand::execute() {
    //region Edge Case-handling
    if(!classifier.isThereTestData()) {
        dio->write("No testing data was given!\n");
        return;
    } else if(!classifier.wasClassified()) {
        classifier.defItems();
    }
    //endregion

    //region Var Initialization
    std::vector<Item> results = classifier.getTestOutputData();
    std::vector<Item> answers = classifier.getTestInputData();
    std::vector<std::string> types = classifier.getTypes(answers);

    int confusionCount[types.size()][types.size() + 1];

    //might need to figure out memset later...
    for(int i = 0; i < types.size(); i++) {
        for(int j = 0; j < types.size() + 1; j++) {
            confusionCount[i][j] = 0;
        }
    }
    //endregion

    //region CalculatingConfusionMatrix
    for(int i = 0; i < answers.size(); i++) {
        int iPos = findPosInVector(types, answers[i]);
        int jPos = findPosInVector(types, results[i]);

        if(iPos < 0 || jPos < 0) {
            throw std::exception();
        }

        confusionCount[iPos][jPos]++;
        confusionCount[iPos][types.size()]++;
    }
    //endregion

    //region PrintingConfusionMatrix
    std::string output = "";
    for(int i = 0; i < types.size(); i++) {
        output += types[i];
        for(int j = 0; j < types.size(); j++) {
            output += "\t";
            output += (confusionCount[i][j] * 100)/confusionCount[i][types.size()];
            output += "%";
        }
        output += "\n";
    }
    for(int i = 0; i < types.size(); i++) {
        output += "\t";
        output += types[i];
    }
    output += "\n\n";
    output += SettingsCommand::stringSettings(classifier) + "\n";
    dio->write(output);
    //endregion
}

int ConfusionMatrixCommand::findPosInVector(const std::vector<std::string> v, const Item &item) {
    for(int i = 0; i < v.size(); i++) {
        if (v[i] == item.getTypeOfItem()) {
            return i;
        }
    }
    return -1;
}
