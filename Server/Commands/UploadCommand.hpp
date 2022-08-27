#ifndef KNNCLASSIFIER3_0_UPLOADCOMMAND_HPP
#define KNNCLASSIFIER3_0_UPLOADCOMMAND_HPP

#include "Server/Commands/Command.hpp"

class UploadCommand : public Command {
private:
    std::vector<Item>& updateFromFile(const std::string& path);
    Item& itemFromLine(char *st);
        public:
    UploadCommand(Classifier &classifier, DefaultIO *dio);
    void execute() override;
};


#endif //KNNCLASSIFIER3_0_UPLOADCOMMAND_HPP
