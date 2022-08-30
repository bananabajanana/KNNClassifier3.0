#include "Client.hpp"
#define CLIENT_PORT 6969
#define MY_IP "127.0.0.1"

int main() {
    ClientProcess client(MY_IP, CLIENT_PORT);
    client.runClient();
}