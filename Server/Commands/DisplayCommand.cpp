#include "DisplayCommand.hpp"

DisplayCommand::DisplayCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "display results") {}

void DisplayCommand::execute() {
    if(!classifier.isThereUnclassifiedItems()) {
        dio->write("No testing data was given!");
        return;
    }

    const std::vector<Item> toPrint = classifier.getTestOutputData();
    std::string output = "";
    for(int i = 0; i<toPrint.size(); i++) {
        output += (i+1);
        output += " " + toPrint[i].getTypeOfItem() + "\n";
    }
    output += "Dont.\n";
    dio->write(output);
    return;
}