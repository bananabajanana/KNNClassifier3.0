#ifndef KNNCLASSIFIER3_0_CLI_HPP
#define KNNCLASSIFIER3_0_CLI_HPP

#include <vector>
#include "Server/Commands/Command.hpp"

/**
 * TODO:
 *      - Generalize old classifier
 *          - work with general string instead of enum.
 *          - input function needs to figure out nth rank.
 *          - work with 3 vectors.
 *      - Implement Commands
 *      - Implement IO Services
 *      - Implement Command Line Interface
 *      - Make sure there are no memory leaks!!! (used new)
 */

class CLI {
private:
    std::vector<Command> commands;
    DefaultIO *dio;
public:
    void start();
};


#endif //KNNCLASSIFIER3_0_CLI_HPP
