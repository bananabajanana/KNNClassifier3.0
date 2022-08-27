#include "ClassifyCommand.hpp"

ClassifyCommand::ClassifyCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "classify data"){}

void ClassifyCommand::execute() {
    classifier.defItems();
    dio->write("classifying data complete\n");
    return;
}