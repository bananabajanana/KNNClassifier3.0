#ifndef KNNCLASSIFIER_SERVERPROCESS_HPP
#define KNNCLASSIFIER_SERVERPROCESS_HPP

#ifdef WIN32
#include <windows.h>
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#endif
#include <vector>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Server/Classifier/Item.hpp"
#include "Server/Classifier/srcDistances/DistanceCalc.hpp"
#include "Server/Classifier/Classifier.hpp"
#include "Server/CLI.hpp"

#define SERVER_PORT 6969
#define CLIENT_TIME_OUT 15
#define MAX_CLIENTS_NUM 1024
#include "pthread.h"

class ServerProcess {
private:
    struct ThrParams {
        ThrParams() : buf(0){}
        char* buf;
        CLI cli;
    };


    int listeningSock;
    int client_socks[MAX_CLIENTS_NUM];
    //select() requires the size of the array of sockets to be passed as the maximum socket number plus one.
    //see the man page of select.
    int maxFd;
    int maxFdsPlusOne;
    int clientsNum;
    //the set of all the sockets the our server has.
    fd_set rfds;
    //responsible for the time out.
    struct timeval tv;

    void releaseResources();
    int OnInputFromClient(int fd);
    int searchMaxFd();
    /**
     * Creating the listening sock and do the first steps that a server need to do - bind.
     * @param server_port - the server port.
     * @return the listening sock.
     */
    int serverInitialization(const int server_port);

    /**
     * Start the listening stage.
     * @param sock - the socket.
     */
    void listenSoc(int sock);
    /**
     * Start the accept stage.
     * @param sock - the socket.
     * @param client_sin - the client.
     * @return
     */
    int acceptSoc(int sock, struct sockaddr_in client_sin);
    /**
     * Creating the output (a flower) that we can define by it its type.
     * @param properties - the flower properties
     * @param machine - the Classifier which
     * @param fc - the object that can help us to convert input to things that we can work with.
     * @return The output as flower.
     */
    Item defFlowerSoc(char* properties, Classifier machine);
    /**
     * Sends the output to the client
     * @param unclassified - the flower that we had to define.
     * @param fc - the object that can help us to convert input to things that we can work with.
     * @param client_sock - get the client.
     */
    void sendSoc(Item unclassified, int client_sock);
public:
    /**
     * Creating server.
     */
    ServerProcess();
    /**
     * Start to talk with clients, get input and sent output.
     * @param machine - the Classifier which
     * @param fc - the object that can help us to convert input to things that we can work with.
     */
    void ServerRunner(Classifier machine);

    static void* threadFunc(void* arg);
};
#endif //KNNCLASSIFIER_SERVERPROCESS_HPP