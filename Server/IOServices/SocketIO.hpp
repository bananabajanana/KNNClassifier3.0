#ifndef KNNCLASSIFIER3_0_SOCKETIO_HPP
#define KNNCLASSIFIER3_0_SOCKETIO_HPP

#include "Server/IOServices/DefaultIO.hpp"

class SocketIO : public DefaultIO {
private:
    int socket;
    int expected_data_len = 128;
public:
    SocketIO(int socket);
    std::string read() override;
    void write(std::string toWrite) override;

};


#endif //KNNCLASSIFIER3_0_SOCKETIO_HPP
