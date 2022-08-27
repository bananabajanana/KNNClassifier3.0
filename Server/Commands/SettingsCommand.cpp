#include "SettingsCommand.hpp"

SettingsCommand::SettingsCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "algorithm settings") {
}

std::string SettingsCommand::stringSettings(Classifier &classifier) {
    std::string output = "The current KNN parameters are: K = " + classifier.getK();
    output += ", distance metric = " + classifier.getDistanceType()->fileName();
    return output;
}

void SettingsCommand::execute() {
    std::string message = stringSettings(classifier) + "\n";
    dio->write(message);
    std::string input = dio->read();
    if (input.empty()) {
        return;
    }
    while (true) {
        std::string kValue;
        std::string metValue;
        try {
            char *messagePtr = strdup(message.c_str());
            kValue = strtok(messagePtr, " ");
            metValue = strtok(nullptr, " ");
        } catch (std::exception &e) {
            dio->write("Invalid amount of arguments. Should be \"{k} {metric}\"");
            continue;
        }

        int newK;
        try {
            newK = std::stoi(kValue);
            if (newK < 1 || newK > 10) {
                dio->write("Invalid value for K");
                continue;
            }
        } catch (std::exception &e) {
            dio->write("Invalid value for K");
            continue;
        }

        if(metValue != "EUC" && metValue != "MAN" && metValue != "CHE") {
            dio->write("Invalid value for distance metric");
            continue;
        }

        classifier.setK(newK);
        DistanceCalc *old = classifier.getDistanceType();

        //not really _oopy_, should probably fix later.
        if (metValue == "EUC") {
            classifier.setDistanceType(new EuclideanDistance);
        } else if(metValue == "MAN") {
            classifier.setDistanceType(new ManhattanDistance);
        } else {
            classifier.setDistanceType(new ChebyshevDistance);
        }
        delete old;
    }
}