#include "Server/ServerCode/ServerProcess.hpp"

/**
 * TODO:
 *      - Maybe generalize confusion matrix printing method (types with long names)
 */

int main() {
    ServerProcess *server = new ServerProcess();
    server->ServerRunner();
    delete server;
}