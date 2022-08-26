#include "Command.hpp"

Command::Command(Classifier &classifier, DefaultIO *dio, std::string description) : classifier(classifier), dio(dio), description(description) {
}

std::string Command::getDescription() {
    return description;
}