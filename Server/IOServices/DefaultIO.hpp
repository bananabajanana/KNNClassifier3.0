#ifndef KNNCLASSIFIER3_0_DEFAULTIO_HPP
#define KNNCLASSIFIER3_0_DEFAULTIO_HPP

#include <string>
#include <iostream>

class DefaultIO {
public:
    virtual std::string read() = 0;
    virtual void write(std::string toWrite) = 0;
    virtual ~DefaultIO() = default;
};


#endif //KNNCLASSIFIER3_0_DEFAULTIO_HPP
