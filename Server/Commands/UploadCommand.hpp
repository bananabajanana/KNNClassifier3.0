#ifndef KNNCLASSIFIER3_0_UPLOADCOMMAND_HPP
#define KNNCLASSIFIER3_0_UPLOADCOMMAND_HPP

#include "Server/Commands/Command.cpp"

class UploadCommand : public Command {
public:
    UploadCommand(Classifier &classifier, DefaultIO *dio);
};


#endif //KNNCLASSIFIER3_0_UPLOADCOMMAND_HPP
