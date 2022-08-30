#ifndef KNNCLASSIFIER3_0_CLI_HPP
#define KNNCLASSIFIER3_0_CLI_HPP

#include <vector>
#include "Server/Commands/Command.hpp"
#include "Server/Commands/ClassifyCommand.hpp"
#include "Server/Commands/ConfusionMatrixCommand.hpp"
#include "Server/Commands/DisplayCommand.hpp"
#include "Server/Commands/DownloadCommand.hpp"
#include "Server/Commands/SettingsCommand.hpp"
#include "Server/Commands/UploadCommand.hpp"
#include "ServerProcess.hpp"

class ServerProcess;
class CLI {
private:
    std::vector<Command *> commands;
    DefaultIO *dio;
public:
    /**
     * Starts the Command line interface interaction between the server and a single user.
     */
    void start();
    CLI(int fd, ServerProcess &server);
};


#endif //KNNCLASSIFIER3_0_CLI_HPP
