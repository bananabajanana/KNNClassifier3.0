#include "Client.hpp"

ClientProcess::ClientProcess(char *ip_address, int port_no) {
    this->ip_address = ip_address;
    this->port_no = port_no;
}

void ClientProcess::sendMessage(std::string message) {
    message += '\003';//to make sure full message was sent on the other side
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

    //sending the server the content of the file one by one.
    //after each line, waiting for a server response to make sure the line was recieved
    //so file won't get corrupted
    while(std::getline(input, message)) {
        sendMessage(message);
        if(getMessage() != "\\next\n") {
            perror("File Transfer failed!");
        }
    }
    sendMessage("DONE");//confirming this is the end of the message
    input.close();
}

std::string ClientProcess::getMessage() {
    std::string output = "";
    char buffer[4096]={0};
    do {
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            throw std::runtime_error("Client Error: Server closed the connection");
        } else if (read_bytes < 0) {
            throw std::runtime_error("Client Error: Couldn't sent bytes to server");
        }
        output += buffer;
    } while (output[output.length() - 1] != '\003'); //reads from socket until we reached the ending char
    output.pop_back();//removes the '\003' char
    return output;
}

void ClientProcess::getFile(std::string path) {
    std::ofstream output(path);

    sendMessage("\\next");//asks for the first line of the file
    std::string line = getMessage();

    //after receiving each line from the server and writing it to a file
    //asks for the next line as confirmation the previous line was saved
    while(line != "DONE\n") {
        output << line;
        sendMessage("\\next\n");
        line = getMessage();
    }
    sendMessage("\\received\n");//confirming the full file was received
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

void ClientProcess::uploadCommand(std::string args) {
    std::string message;
    std::cout << "Please upload your local " << args << " CSV file." << std::endl;
    std::getline(std::cin, message);
    sendFile(message);
}

void ClientProcess::downloadCommand(std::string args) {
    std::string message;
    std::cout << "Please give a path to download " << args << " to." << std::endl;
    std::getline(std::cin, message);
    getFile(message + args);
}

void ClientProcess::generalCommand(std::string message) {
    std::cout << message;

    std::getline(std::cin, message);
    if (message.empty()) {
        sendMessage("\\empty");
    } else {
        sendMessage(message);
    }
}

void ClientProcess::runClient() {
    sock = connectToServer();

    std::string message;
    while(true) {
        try {
            message = getMessage();

            //managing Server-Client commands
            //(mostly file manipulation like upload and download file)
            if (message.find('\\') != std::string::npos) {

                //printing text before command
                if(message.find('\\') != 0) {
                    std::cout << message.substr(0, message.find("\\")) << std::endl;
                    message = message.substr(message.find("\\"), message.length() - message.find("\\"));
                }

                char *messageArr = const_cast<char *>(message.c_str());
                std::string command = strtok(messageArr, " ");
                std::string argument = strtok(nullptr, "\n");

                if (command == "\\upload") {
                    uploadCommand(argument);
                } else if (command == "\\download") {
                    downloadCommand(argument);
                } else {
                    //region Unknown command handling
                    message = "Client Error: " + command;
                    message += " with arguments " + argument;
                    message += " doesn't exist.\n";
                    throw std::runtime_error(message);
                    //endregion
                }
            } else {
                generalCommand(message);
            }
        } catch (std::runtime_error &e) {
            if (strcmp(e.what(), "Client Error: Server closed the connection") == 0) {
                return;
            } else {
                std::cout << e.what();
                return;
            }
        }
    }
}