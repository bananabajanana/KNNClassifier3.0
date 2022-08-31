#ifndef KNNCLASSIFIER3_0_DOWNLOADCOMMAND_HPP
#define KNNCLASSIFIER3_0_DOWNLOADCOMMAND_HPP

#include "Server/Commands/Command.hpp"

class DownloadCommand : public Command {
public:
    /**
    * Constructor
    */
    DownloadCommand(Classifier &classifier, DefaultIO *dio);

    void execute();
};


#endif //KNNCLASSIFIER3_0_DOWNLOADCOMMAND_HPP
