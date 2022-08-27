#ifndef KNNCLASSIFIER3_0_CLI_HPP
#define KNNCLASSIFIER3_0_CLI_HPP

#include <vector>
#include "Server/Commands/Command.hpp"

/**
 * TODO:
 *      - Generalize old classifier
 *          - input function needs to figure out nth rank.
 *      - Implement Commands
 *      - Implement IO Services
 *      - Implement Command Line Interface
 *      - Make sure there are no memory leaks!!! (used new)
 *
 * MICHALLLLLL:
 *      - I changed the names of the vectors to "TrainingData, inputTestData, outputTestData"
 */

class CLI {
private:
    std::vector<Command> commands;
    DefaultIO *dio;
public:
    /**
     * Starts the Command line interface interaction between the server and a single user.
     */
    void start();
};


#endif //KNNCLASSIFIER3_0_CLI_HPP
