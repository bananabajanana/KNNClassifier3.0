#include "DownloadCommand.hpp"

DownloadCommand::DownloadCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "download results") {}