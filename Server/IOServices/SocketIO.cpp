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
    //region SendingBacklog
    toSend += '\003';
    char* toSendArr = const_cast<char *>(toSend.c_str());
    int message_len = strlen(toSendArr);
    int sent_bytes = send(socket, toSendArr, message_len, 0);

    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    toSend = "";
    //endregion

    //region Reading new Message
    std::string output = "";
    char buffer[4096]={0};
    do {
        int read_bytes = recv(socket, buffer, expected_data_len, 0);
        if (read_bytes <= 0) {
            server.deleteSocket(socket);
            return "7";
        }
        output += buffer;
    } while(output[output.length() - 1] != '\003');
    output.pop_back();
    return output;
    //endregion
}

void SocketIO::write(std::string message) {
    toSend += message;

}

SocketIO::SocketIO(int socket, ServerProcess &s) :socket(socket), server(s) {
    toSend = "";
}