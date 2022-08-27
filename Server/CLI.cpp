#include "CLI.hpp"
int main() {
    CLI ohad;
    ohad.start();
}

void CLI::start() {
    while(true) {
        //region Menu Printing
        std::string menu = "Welcome to the KNN Classifier Server. Please chose an option:\n";
        for(int i = 1; i <= commands.size(); i++) {
            menu += i + ". ";
            menu += commands[i].getDescription() + "\n";
        }
        menu += (commands.size()+1) + ". exit\n";

        dio->write(menu);
        //endregion

        //region Chose command
        std::string decision = dio->read();
        try {
            int numDecision = std::stoi(decision) - 1;

            //exit the server/close the connection
            if (numDecision == commands.size()) {
                return;
            }


            if(numDecision < 0 || numDecision > commands.size()) {
                commands[numDecision].execute();
            } else {
                dio->write("Please chose a valid option.");
            }
        } catch(std::exception& e) {
            dio->write("Please select an option by writing a number.");
        }
        //endregion
    }
}