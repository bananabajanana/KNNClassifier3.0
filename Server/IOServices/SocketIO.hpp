#ifndef KNNCLASSIFIER3_0_SOCKETIO_HPP
#define KNNCLASSIFIER3_0_SOCKETIO_HPP

#include "Server/IOServices/DefaultIO.hpp"
#include "Server/ServerCode/ServerProcess.hpp"

class ServerProcess;
class SocketIO : public DefaultIO {
private:
    int socket;
    int expected_data_len = 4096;
    std::string toSend;
    ServerProcess server;
public:
    /**
     * Constructor
     * @param socket socket number for IO
     * @param s Server that opened this SocketIO
     */
    SocketIO(int socket, ServerProcess &s);

    /**
     * @return a message from the socket
     */
    std::string read() override;

    /**
     * Write a message to the socket
     * @param toWrite message to send
     */
    void write(std::string toWrite) override;

    ~SocketIO() override;

};


#endif //KNNCLASSIFIER3_0_SOCKETIO_HPP
