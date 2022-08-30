#include "ServerProcess.hpp"
#include <thread>
#include <mutex>

ServerProcess::ServerProcess() {
    listeningSock = serverInitialization(SERVER_PORT);
    listenSoc(listeningSock);

    memset((void*)client_socks,0,sizeof(client_socks));
    //select() requires the size of the array of sockets to be passed as the maximum socket number plus one.
    //see the man page of select.
    maxFd = 0;
    maxFdsPlusOne = listeningSock + 1;
    clientsNum = 0;
    FD_ZERO(&rfds);
    FD_SET(listeningSock, &rfds);
    tv.tv_sec = CLIENT_TIME_OUT;
    tv.tv_usec = 0;
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
    for(int i=0; i< MAX_CLIENTS_NUM;i++) {
        if(client_socks[i]) {
            close(client_socks[i]);
        }
    }
    close(listeningSock);
    //close threads!
    // Iterate the map and make pthread_join to wait for all active threads.
}

int ServerProcess::acceptSoc(int sock, struct sockaddr_in client_sin) {
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");

    }
    return client_sock;
}


int ServerProcess::searchMaxFd() {
    int i=maxFd;
    for(;i>=0;i--) {
        if(client_socks[i]) {
            break;
        }
    }
    return i;
}
int ServerProcess::OnInputFromClient(const int fd) {
    char buffer[128];
    int expected_data_len = sizeof(buffer);
    int read_bytes = 1;
    do
    {
        //region Manual buffer memset because of bug
        for (int i = 0; i < 20; i++) {
            buffer[i] = '\0';
        }
        //endregion

        int read_bytes = recv(fd, buffer, expected_data_len, 0);
        if (read_bytes <= 0)
        {
            clientsNum--;
            client_socks[fd]=0;
            maxFd = searchMaxFd();
            //maximum of all client_sockets +1
            maxFdsPlusOne = std::max(listeningSock, maxFd) + 1;
            FD_CLR(fd,&rfds);

            close(fd);
            if(read_bytes<0) {
                perror("recive returned -1");
            } else {
                std::cout<<"client closed connection.";
            }
            break;
        }
        char* threadInputBuffer = new (std::nothrow) char[read_bytes];
        if(threadInputBuffer== nullptr) {
            perror("there is no memory.");
            break;
        }
        // Check which input is required by defFlowerSoc
        memcpy(threadInputBuffer,buffer,read_bytes);

        ThrParams* thrParams = new ThrParams;
        thrParams->buf = threadInputBuffer;
        thrParams->cli = new CLI(new SocketIo(fd));
        thrParams->socket=fd;
        pthread_t threadId;
        int res = pthread_create(&threadId, NULL,threadFunc, thrParams);
        if(res == -1) {
            perror("pthread_create failed");
            return -1;
        }
        threadsMap.insert(std::pair<int, int>(threadId, threadId));
        //add to map threadId


    }while (read_bytes != 0);
}

void ServerProcess::ServerRunner(Classifier machine) {

    while(true) {
        int retval = select(maxFdsPlusOne, &rfds, NULL, NULL, &tv);
        if(retval==-1) {
            //error the socket is not right
            perror("There is an error with the socket.");
            exit(1);
        }
        if(retval==0) {
            //there is time out
            releaseResources();
            exit(2);
        }
        //retval is positive number. that means that one of our sockets recived data or
        //our listening socket recived a new connection that we need to accept.
        if(FD_ISSET(listeningSock,&rfds)) {
            // event on listening socket - accepting new clients
            struct sockaddr_in client_sin;
            int clientFd = acceptSoc(listeningSock, client_sin);
            if(clientFd==-1) {
                return;
            }
            clientsNum++;
            if( clientFd < MAX_CLIENTS_NUM) {
                this->client_socks[clientFd] = 1;
                if(maxFd < clientFd) {
                    maxFd = clientFd;
                }
            }
            //maximum of all client_sockets +1
            maxFdsPlusOne = std::max(listeningSock, maxFd) + 1;
            FD_SET(clientFd, &rfds);
        }
        else
        {
            for(int fd = 0; fd <= maxFd; fd++) {
                if(FD_ISSET( fd, &rfds)) {
                    OnInputFromClient(fd);
                }
            }

        }//else
    } // while(true)
}
//static
void* ServerProcess::threadFunc(void* args) {
    ThrParams* params = (ThrParams*)args;

    Item unclassified = defFlowerSoc(params->buf, machine, fc);
    sendSoc(unclassified, fd);

    delete params->buf;
    delete params->cli;
    delete params;
    // also CLI delete

    pthread_t pid = pthread_self();
    std::mutex locker;
    locker.lock();
    threadsMap.erase(pid);
    locker.unlock();
    //remove pid from static map
}
