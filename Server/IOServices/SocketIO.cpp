#include "SocketIO.hpp"
#ifdef WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <string.h>
bool hasChar(char *arr, int n, char c) {
    for(int i = 0; i < n; i++) {
        if (arr[i] == c) {
            return true;
        }
    }
    return false;
}

std::string SocketIO::read() {
    std::string output = "";
    char buffer[1024]={0};
    int read_bytes = recv(socket, buffer, expected_data_len, 0);
    if (read_bytes <= 0) {
        server.deleteSocket(socket);
        return "7";
    }
    output += buffer;
    output[output.length() - 1] = '\0';
    return output;
}

void SocketIO::write(std::string message) {
    char* toSend = const_cast<char *>(message.c_str());
    int message_len = strlen(toSend);
    int sent_bytes = send(socket, toSend, message_len, 0);

    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}

SocketIO::SocketIO(int socket, ServerProcess &s) :socket(socket), server(s) {}