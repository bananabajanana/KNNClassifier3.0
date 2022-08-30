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
    std::string message = "Please upload your local train CSV file.\n";
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
    std::vector<std::string> parameters;
    val = strtok(st, ",");
    while( val != NULL ) {
        parameters.push_back(val);
        val = strtok(nullptr, ",");
    }
    std::vector<double> p;
    for(int i=0; i<parameters.size() - 1;i++) {
        p.push_back(std::stod(parameters[i]));
    }
    Item* output = new Item(p);
    auto it = parameters[parameters.size()-1].begin();
    //not good
    if(std::isdigit(*it)) {
        output->pushProperty(std::stod(parameters[parameters.size()-1]));
    } else {
        std::string temp(parameters[parameters.size()-1]);
        output->setType(temp);
    }

    return *output;
}