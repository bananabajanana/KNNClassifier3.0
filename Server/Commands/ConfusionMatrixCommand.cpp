#include "ConfusionMatrixCommand.hpp"


ConfusionMatrixCommand::ConfusionMatrixCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "display algorithm confusion matrix") {}

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
    std::vector<std::string> types;
    Classifier::addTypes(results, types);
    Classifier::addTypes(answers, types);

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

    int maxChars = 4;
    for(int i = 0; i < types.size(); i++) {
        if(types[i].length() > maxChars) {
            maxChars = types[i].length();
        }
    }

    for(int i = 0; i < types.size(); i++) {
        output += types[i];
        for(int j = 0; j < types.size(); j++) {
            if (confusionCount[i][types.size()] > 0) {
                output += "\t\t";
                output += std::to_string((confusionCount[i][j] * 100) / confusionCount[i][types.size()]);
                output += "%";
            } else {
                output += "\t\t0%";
            }
        }
        output += "\n";
    }
    for(int i = 0; i < types.size(); i++) {
        output += "\t\t";
        output += types[i];
    }
    output += "\n\n";
    output += SettingsCommand::stringSettings(classifier) + "\n";
    dio->write(output);
    //endregion
}

int ConfusionMatrixCommand::findPosInVector(const std::vector<std::string>& v, const Item &item) {
    for(int i = 0; i < v.size(); i++) {
        if (v[i] == item.getTypeOfItem()) {
            return i;
        }
    }
    return -1;
}
