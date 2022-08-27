#include "UploadCommand.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
UploadCommand::UploadCommand(Classifier &classifier, DefaultIO *dio) : Command(classifier, dio, "upload an unclassified csv data file")
{}
void UploadCommand::execute()
{
    std::string message = "Please upload your local tran CSV file.";
    std::vector<Item> content;
    dio->write(message);
    std::string input = dio->read();
    //maybe it should be the "done!"
    if (input.empty()) {
        return;
    }
    while(input!="DONE"){
        char* info = const_cast<char *>(input.c_str());
        content.push_back(itemFromLine(info));
        input = dio->read();
        if (input.empty()) {
            return;
        }
    }
}

Item& UploadCommand::itemFromLine(char *st) {
    char * val;
    double parameters[4];
    val = strtok(st, ",");
    for(double& param : parameters) {
        param = std::stod(val);
        val = strtok(nullptr, ",");
    }
    Item* output = new Item(parameters, 4);
    if (val != nullptr) {
        std::string temp(val);
        output->setType(temp);
    }
    return *output;
}