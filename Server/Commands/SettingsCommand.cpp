#include "SettingsCommand.hpp"

SettingsCommand::SettingsCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "algorithm settings") {
}

std::string SettingsCommand::stringSettings(Classifier &classifier) {
    std::string output = "The current KNN parameters are: K = " + std::to_string(classifier.getK());
    output += ", distance metric = " + classifier.getDistanceType()->toString();
    output += "\n";
    return output;
}

void SettingsCommand::execute() {
    //write settings
    std::string message = stringSettings(classifier);
    dio->write(message);
    std::string input;

    while (true) {
        input = dio->read();

        if (input == "\\empty") {
            return;
        }

        //region Try Converting Variables
        std::string kValue;
        std::string metValue;
        try {
            char *inputPtr = strdup(input.c_str());
            kValue = strtok(inputPtr, " ");
            metValue = strtok(nullptr, " ");
        } catch (std::exception &e) {
            dio->write("Invalid amount of arguments. Should be \"{k} {metric}\"\n");
            continue;
        }

        int newK;
        try {
            newK = std::stoi(kValue);
            if (newK < 1 || newK > 10) {
                dio->write("Invalid value for K\n");
                continue;
            }
        } catch (std::exception &e) {
            dio->write("Invalid value for K\n");
            continue;
        }

        if(metValue != "EUC" && metValue != "MAN" && metValue != "CHE") {
            dio->write("Invalid value for distance metric\n");
            continue;
        }

        classifier.setK(newK);
        DistanceCalc *old = classifier.getDistanceType();

        if (metValue == "EUC") {
            classifier.setDistanceType(new EuclideanDistance);
        } else if(metValue == "MAN") {
            classifier.setDistanceType(new ManhattanDistance);
        } else {
            classifier.setDistanceType(new ChebyshevDistance);
        }
        delete old;
        //endregion
    }
}