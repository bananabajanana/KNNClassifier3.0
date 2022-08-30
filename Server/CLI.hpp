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
#include "Server/IOServices/StandardIO.hpp"

/**
 * TODO:
 *      - Implement Server Socket Management
 *      - Add threading to commands
 *      - Make sure there are no memory leaks!!! (used new)
 *      - Maybe generalize confusion matrix printing method (types with long names)
 *
 * MICHALLLLLL:
 *      - I changed the names of the vectors to "TrainingData, inputTestData, outputTestData"
 */

class CLI {
private:
    std::vector<Command *> commands;
    DefaultIO *dio;
public:
    /**
     * Starts the Command line interface interaction between the server and a single user.
     */
    void start();
    CLI(DefaultIO *dio);
};


#endif //KNNCLASSIFIER3_0_CLI_HPP
