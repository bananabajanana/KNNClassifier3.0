#ifndef KNNCLASSIFIER_SERVERPROCESS_HPP
#define KNNCLASSIFIER_SERVERPROCESS_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Server/Classifier/Item.hpp"
//#include "Server/IOServices/SocketIO.hpp"
#include "Server/Classifier/srcDistances/DistanceCalc.hpp"
#include "Server/Classifier/Classifier.hpp"
#include "CLI.hpp"

#define SERVER_PORT 6969
#define CLIENT_TIME_OUT 100
#define MAX_CLIENTS_NUM 1024
#include <pthread.h>
#include <map>
#include <thread>
#include <mutex>

class ServerProcess {
private:
    //endregion
//region Menu Printing
    int listeningSock;
    int client_socks[MAX_CLIENTS_NUM];
    int maxFd;
    //select() requires the size of the array of sockets to be passed as the maximum socket number plus one.
    //see the man page of select.
    int maxFdsPlusOne;
    int clientsNum;
    //the set of all the sockets the our server has.
    fd_set rfds;
    //responsible for the time out.
    struct timeval tv;

    /**
     * in the end-life of the server, the server will release its resources.
     */
    void releaseResources();
    /**
     *
     * @param fd
     * @return
     */
    int OnInputFromClient(const int fd);
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
public:
    static std::map<int, int> threadsMap;

    /**
     * Creating server.
     */
    ServerProcess();
    /**
     * Start to talk with clients, get input and sent output.
     * @param machine - the Classifier which
     * @param fc - the object that can help us to convert input to things that we can work with.
     */
    void ServerRunner();

    static void* threadFunc(void* arg);
    void deleteSocket(int fd);
    };
#endif //KNNCLASSIFIER_SERVERPROCESS_HPP