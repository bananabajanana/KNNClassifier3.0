#ifndef KNNCLASSIFIER_CLIENT_HPP
#define KNNCLASSIFIER_CLIENT_HPP

#ifdef WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fstream>

class ClientProcess {
private:
    char* ip_address;
    int expected_data_len = 4096;
    int port_no;
    int sock;


    /**
     * Send a message to the server.
     * @param message message to send to the server
     */
    void sendMessage(std::string message);

    /**
     * Send a file to the server
     * @param path file's path
     */
    void sendFile(const std::string& path);

    /**
     * Manages the special \\upload command
     * @param args path of input file
     */
    void uploadCommand(std::string args);

    /**
     * Manages the special \\download command
     * @param args path of output file
     */
    void downloadCommand(std::string args);

    /**
     * Manages any non-specific command
     */
    void generalCommand(std::string message);

    /**
     * Load a message from the server to the object's buffer array.
     */
    std::string getMessage();

    /**
     * load a file from the server
     * @param path path of file to load to.
     */
    void getFile(std::string path);

    /**
     * Connect to the server with the given port and ip from the initializer.
     * @return socket number
     */
    int connectToServer();
public:
    /**
     * ClientProcess Initializer.
     * @param ip_address server's IP address
     * @param port_no server's port number
     */
    ClientProcess(char* ip_address, int port_no);

    /**
     * Runs a demo functionality of the client.
     * This opens the input file, and feeds each flower information line from it to the server.
     * Then, when receiving the flower's class, it writes it to an output file.
     */
    void runClient();
};

#endif //KNNCLASSIFIER_CLIENT_HPP