#include "CLI.hpp"

void CLI::start() {
    while(true) {
        std::string menu = "Welcome to the KNN Classifier Server. Please chose an option:\n";
        for(int i = 0; i < commands.size(); i++) {
            menu += i + ". ";
            menu += commands[i].getDescription() + "\n";
        }
        dio->write(menu);
        std::string decision = dio->read();
        try {
            commands[std::stoi(decision)];
        } catch(std::exception& e) {
            dio->write("Please select an option by writing a number.");
        }
    }
}