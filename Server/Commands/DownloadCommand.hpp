#ifndef KNNCLASSIFIER3_0_DOWNLOADCOMMAND_HPP
#define KNNCLASSIFIER3_0_DOWNLOADCOMMAND_HPP

#include "Server/Commands/Command.cpp"

class DownloadCommand : public Command {
public:
    DownloadCommand(Classifier &classifier, DefaultIO *dio);
};


#endif //KNNCLASSIFIER3_0_DOWNLOADCOMMAND_HPP
