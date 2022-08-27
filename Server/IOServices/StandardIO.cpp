#include "StandardIO.hpp"

std::string StandardIO::read() {
    std::string st;
    std::getline(std::cin, st);
    return st;
}

void StandardIO::write(std::string toWrite) {
    std::cout << toWrite;
}