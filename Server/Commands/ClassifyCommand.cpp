#include "ClassifyCommand.hpp"

ClassifyCommand::ClassifyCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "classify data"){}

void ClassifyCommand::execute() {
    if (classifier.isThereTestData() && classifier.isThereTrainingData()) {
        classifier.defItems();
        dio->write("classifying data complete\n");
    } else {
        dio->write("Please input data to classify by choosing {1}!\n");
    }
}