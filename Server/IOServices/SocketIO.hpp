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
    SocketIO(int socket, ServerProcess &s);
    std::string read() override;
    void write(std::string toWrite) override;
};


#endif //KNNCLASSIFIER3_0_SOCKETIO_HPP
