#include "ServerProcess.hpp"
std::map<pthread_t, pthread_t> ServerProcess::threadsMap;

ServerProcess::ServerProcess() {
    listeningSock = serverInitialization(SERVER_PORT);
    listenSoc(listeningSock);
    memset((void*)client_socks,0,sizeof(client_socks));
    //select() requires the size of the array of sockets to be passed as the maximum socket number plus one.
    //see the man page of select.
    maxFdsPlusOne = listeningSock + 1;
    clientsNum = 0;
    tv.tv_sec = CLIENT_TIME_OUT;
    tv.tv_usec = 0;
    FD_ZERO(&rfds_listen);
    FD_SET(listeningSock, &rfds_listen);
}

int ServerProcess::serverInitialization(const int server_port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    const int enable = 1;
    //in TCP after closing the program the socket still remains in kernel bound to the port.
    //to prevent failure of the bind() on restarting the program, mark the socket to reuse the address.
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    return sock;
}

void ServerProcess::listenSoc(int sock) {
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
}

void ServerProcess::releaseResources() {
    //Release of the resources.
    close(listeningSock);

    for(auto i:threadsMap) {
        pthread_join(i.first,NULL);
    }
    // Iterate the map and make pthread_join to wait for all active threads.

    for(int i=0; i< MAX_CLIENTS_NUM;i++) {
        if(client_socks[i]) {
            close(client_socks[i]);
        }
    }
    //close threads!
}

int ServerProcess::acceptSoc(int sock, struct sockaddr_in client_sin) {
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");

    }
    return client_sock;
}

void ServerProcess::CliCreate(const int fd) {
    CLI* cli = new CLI(fd, *this);
    pthread_t threadId;
    int res = pthread_create(&threadId, NULL,threadFunc, (void*)cli);
    if(res == -1) {
        perror("pthread_create failed");
        return;
    }
    threadsMap.insert(std::pair<pthread_t, pthread_t>(threadId, threadId));
    //add to map threadId
}

void ServerProcess::ServerRunner() {

    while(true) {
        int retval = select(maxFdsPlusOne, &rfds_listen, NULL, NULL, &tv);
        if(retval==-1) {
            //error the socket is not right
            perror("There is an error with the socket.");
            exit(1);
        }
        if(retval==0) {
            //there is time out
            releaseResources();
            return;
        }
        //retval is positive number. that means that one of our sockets recived data or
        //our listening socket recived a new connection that we need to accept.
        if(FD_ISSET(listeningSock,&rfds_listen)) {
            // event on listening socket - accepting new clients
            struct sockaddr_in client_sin;
            int clientFd = acceptSoc(listeningSock, client_sin);
            if(clientFd==-1) {
                return;
            }
            clientsNum++;
            if(clientFd < MAX_CLIENTS_NUM) {
                this->client_socks[clientFd] = 1;
            }
            //creating new thread
            CliCreate(clientFd);
        }
    } // while(true)
}

void ServerProcess::deleteSocket(int fd) {
    client_socks[fd] = 0;
    clientsNum--;
    close(fd);
}

//static
void* ServerProcess::threadFunc(void* args) {
    CLI* cli = (CLI*)args;
    cli->start();
    delete cli;
    // also CLI delete

    pthread_t pid = pthread_self();
    std::mutex locker;
    locker.lock();
    threadsMap.erase(pid);
    locker.unlock();
    //remove pid from static map
    pthread_exit(0);
}