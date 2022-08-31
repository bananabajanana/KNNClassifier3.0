#include "Client.hpp"

bool hasChar(char *arr, int n, char c) {
    for(int i = 0; i < n; i++) {
        if (arr[i] == c) {
            return true;
        }
    }
    return false;
}

ClientProcess::ClientProcess(char *ip_address, int port_no) {
    this->ip_address = ip_address;
    this->port_no = port_no;
}

void ClientProcess::sendMessage(std::string message) {
    char* toSend = const_cast<char *>(message.c_str());
    int message_len = strlen(toSend);
    int sent_bytes = send(sock, toSend, message_len, 0);

    if (sent_bytes < 0) {
        perror("Client Error: Couldn't send bytes to server");
    }
}

void ClientProcess::sendFile(const std::string& path) {
    std::ifstream input(path);
    std::string message;

    while(std::getline(input, message)) {
        sendMessage(message);
        if(getMessage() != "\\next\n") {
            perror("File Transfer failed!");
        }
    }
    sendMessage("DONE");
    input.close();
}

std::string ClientProcess::getMessage() {
    std::string output = "";
    //should probably check memset
    for (int i = 0; i < 1024; i++) {
        buffer[i] = 0;
    }

    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        throw std::runtime_error("Client Error: Server closed the connection");
    } else if (read_bytes < 0) {
        throw std::runtime_error("Client Error: Couldn't sent bytes to server");
    }
    output+=buffer;
    return output;
}

void ClientProcess::getFile(std::string path) {
    std::ofstream output(path);

    std::string line = getMessage();
    while(line != "DONE") {
        output << line << std::endl;
        line = getMessage();
    }
    output.close();
}

int ClientProcess::connectToServer() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    return sock;
}

void ClientProcess::runClient() {
    sock = connectToServer();

    std::string message;
    while(true) {
        try {
            message = getMessage();
            if (message[0] == '\\') {
                char *messageArr = const_cast<char *>(message.c_str());
                std::string command = strtok(messageArr, " ");
                std::string argument = strtok(nullptr, "\n");
                if (command == "\\upload") {
                    std::cout << "Please upload your local " << argument << " CSV file." << std::endl;
                    std::getline(std::cin, message);
                    sendFile(message);
                    message = getMessage();
                    if (message != "Upload complete.\n") {
                        perror("Upload failed");
                    }
                } else if (command == "\\download") {
                    std::cout << "Please give a path to download " << argument << " to.";
                    std::getline(std::cin, message);
                    getFile(message);
                } else {
                    message = "Client Error: " + command;
                    message += " with arguments " + argument;
                    message += " doesn't exist.\n";
                    throw std::runtime_error(message);
                }
            } else {
                std::cout << message;

                std::getline(std::cin, message);
                if (message.empty()) {
                    sendMessage("\\empty");
                } else {
                    sendMessage(message);
                }
            }
        } catch (std::runtime_error &e) {
            if (e.what() == "Client Error: Server closed the connection") {
                return;
            } else {
                std::cout << e.what();
                return;
            }
        }
    }
}