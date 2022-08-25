#ifndef KNNCLASSIFIER3_0_CLI_HPP
#define KNNCLASSIFIER3_0_CLI_HPP

#include <vector>
#include "Server/Commands/Command.hpp"

class CLI {
private:
    std::vector<Command> commands;

public:
    void start();
};


#endif //KNNCLASSIFIER3_0_CLI_HPP
