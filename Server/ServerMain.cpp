#include "Server/ServerCode/ServerProcess.hpp"

int main() {
    ServerProcess *server = new ServerProcess();
    server->ServerRunner();
}