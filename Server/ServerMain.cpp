#include "Server/ServerCode/ServerProcess.hpp"

/**
 * TODO:
 *      - (?) Download Command Threads
 *      - Destructors all around weeeeee (mainly CLI)
 *      - Make sure there are no memory leaks!!! (used new)
 *      - Maybe generalize confusion matrix printing method (types with long names)
 *      - Readme!
 */

int main() {
    ServerProcess *server = new ServerProcess();
    server->ServerRunner();
}