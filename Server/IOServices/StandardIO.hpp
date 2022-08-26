#ifndef KNNCLASSIFIER3_0_STANDARDIO_HPP
#define KNNCLASSIFIER3_0_STANDARDIO_HPP

#include "Server/IOServices/DefaultIO.hpp"

class StandardIO : public DefaultIO {
    std::string read() override;
    void write(std::string toWrite) override;
};


#endif //KNNCLASSIFIER3_0_STANDARDIO_HPP
