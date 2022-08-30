#include "SocketIO.hpp"
#ifdef WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
std::string SocketIO::read() {
    char buffer[128]={0};
    int read_bytes = recv(socket, buffer, expected_data_len, 0);
    return std::string(buffer);
}

void SocketIO::write(std::string message) {
    //message = message + "\003";
    char* toSend = const_cast<char *>(message.c_str());
    int message_len = strlen(toSend);
    int sent_bytes = send(socket, toSend, message_len, 0);

    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}

SocketIO::SocketIO(int socket) :socket(socket) {}