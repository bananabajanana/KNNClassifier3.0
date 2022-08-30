#include "DownloadCommand.hpp"

DownloadCommand::DownloadCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "download results") {}
//same as 4
void DownloadCommand::execute() {
    //region Edge Case-handling
    if(!classifier.isThereTestData()) {
        dio->write("No testing data was given!\n");
        return;
    } else if(!classifier.wasClassified()) {
        dio->write("The testing data was not classified!\nPlease select \"classify data\" before displaying results\n");
        return;
    }
    //endregion

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