#include "Server/ServerCode/ServerProcess.hpp"

/**
 * TODO:
 *      - (?) Download Command Threads
 *      - Destructors all around weeeeee (mainly CLI)
 *      - Make sure there are no memory leaks!!! (used new)
 *      - Maybe generalize confusion matrix printing method (types with long names)
 *      - Comments and readme!
 */

int main() {
    ServerProcess *server = new ServerProcess();
    server->ServerRunner();
}