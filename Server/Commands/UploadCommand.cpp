#include "UploadCommand.hpp"

UploadCommand::UploadCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "upload an unclassified csv data file") {}