#include "ConfusionMatrixCommand.hpp"

ConfusionMatrixCommand::ConfusionMatrixCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "display algorithm confusion matrix"){}