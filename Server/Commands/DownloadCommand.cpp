#include "DownloadCommand.hpp"

DownloadCommand::DownloadCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "download results") {}

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

    dio->write("\\download results.txt\n");
    const std::vector<Item> toPrint = classifier.getTestOutputData();
    if (dio->read() != "\\next") {
        perror("Couldn't send file");
    }
    std::string output = "";
    for(int i = 0; i<toPrint.size(); i++) {
        output = std::to_string(i+1);
        output += " " + toPrint[i].getTypeOfItem() + "\n";
        dio->write(output);
        if(dio->read() != "\\next\n") {
            perror("Couldn't send file");
        }
    }
    dio->write("DONE\n");
    if(dio->read() != "\\received\n") {
        perror("Couldn't send file");
    }
    dio->write("Upload complete\n");
    return;
}