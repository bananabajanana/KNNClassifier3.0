#include "CLI.hpp"
#include "Server/IOServices/SocketIO.hpp"
#include "Server/IOServices/StandardIO.hpp"

CLI::CLI(int fd, ServerProcess &server) : dio(new SocketIO(fd, server)) {
    c = new Classifier(5);

    commands.push_back(new UploadCommand(*c, dio));
    commands.push_back(new SettingsCommand(*c, dio));
    commands.push_back(new ClassifyCommand(*c, dio));
    commands.push_back(new DisplayCommand(*c, dio));
    commands.push_back(new DownloadCommand(*c, dio));
    commands.push_back(new ConfusionMatrixCommand(*c, dio));
}

CLI::CLI() :dio(new StandardIO()){ }

void CLI::start() {
    while(true) {
        //region Menu Printing
        std::string menu = "Welcome to the KNN Classifier Server. Please chose an option:\n";
        for(int i = 1; i <= commands.size(); i++) {
            menu += std::to_string(i) + ". ";
            menu += commands[i-1]->getDescription() + "\n";
        }
        menu += std::to_string(commands.size()+1) + ". exit\n";

        dio->write(menu);
        //endregion
        //region Choose command
        std::string decision = dio->read();
        try {
            int numDecision = std::stoi(decision) - 1;

            //exit the server/close the connection
            if (numDecision == commands.size()) {
                return;
            }

            if(numDecision >= 0 && numDecision <= commands.size()) {
                commands[numDecision]->execute();
            } else {
                dio->write("Please chose a valid option.");
            }
        } catch(std::runtime_error& e) {
            if (strcmp(e.what(), "Connection failed") == 0) {
                return;
            }
            dio->write("Please select an option by writing a number.\n");
        }
        //endregion
    }
}

CLI::~CLI() {
    while(!commands.empty()) {
        Command *temp = commands.back();
        commands.pop_back();
        delete temp;
    }
    delete c;
    delete dio;
}