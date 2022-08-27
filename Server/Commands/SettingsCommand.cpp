#include "SettingsCommand.hpp"

SettingsCommand::SettingsCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "algorithm settings") {}

std::string SettingsCommand::stringSettings(Classifier &classifier) {
    std::string output = "The current KNN parameters are: K = " + classifier.getK();
    output += ", distance metric = " + classifier.getDistanceType()->fileName();
    return output;
}

void SettingsCommand::execute() {
    //region Write Message
    std::string message = stringSettings(classifier) + "\n";
    dio->write(message);
    //endregion

    std::string input = dio->read();

    //until we get a valid input
    while (true) {
        //region Input Empty
        if (input.empty()) {
            return;
        }
        //endregion

        std::string kValue;
        std::string metValue;

        //region Separate the 2 values
        try {
            char *messagePtr = strdup(message.c_str());
            kValue = strtok(messagePtr, " ");
            metValue = strtok(nullptr, " ");
        } catch (std::exception &e) {
            dio->write("Invalid amount of arguments. Should be \"{k} {metric}\"");
            input = dio->read();
            continue;
        }
        //endregion

        //region Parse new K value
        int newK;
        try {
            newK = std::stoi(kValue);
            if (newK < 1 || newK > 10) {
                dio->write("Invalid value for K");
                input = dio->read();
                continue;
            }
        } catch (std::exception &e) {
            dio->write("Invalid value for K");
            input = dio->read();
            continue;
        }
        //endregion

        //region Parse new metric value
        if(metValue != "EUC" && metValue != "MAN" && metValue != "CHE") {
            dio->write("Invalid value for distance metric");
            input = dio->read();
            continue;
        }
        //endregion

        classifier.setK(newK);

        //not really _oopy_, should probably fix later.
        DistanceCalc *old = classifier.getDistanceType();
        if (metValue == "EUC") {
            classifier.setDistanceType(new EuclideanDistance);
        } else if(metValue == "MAN") {
            classifier.setDistanceType(new ManhattanDistance);
        } else {
            classifier.setDistanceType(new ChebyshevDistance);
        }
        if(old != nullptr) {
            delete old;//deleting the previous calculator since it was stored in heap
        }
    }
}