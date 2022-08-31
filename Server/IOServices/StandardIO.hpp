#ifndef KNNCLASSIFIER3_0_STANDARDIO_HPP
#define KNNCLASSIFIER3_0_STANDARDIO_HPP

#include "Server/IOServices/DefaultIO.hpp"

class StandardIO : public DefaultIO {
    /**
     * @return message from console
     */
    std::string read() override;

    /**
     * Write a message to the console
     * @param toWrite message to write
     */
    void write(std::string toWrite) override;
};


#endif //KNNCLASSIFIER3_0_STANDARDIO_HPP
