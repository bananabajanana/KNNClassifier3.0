#ifndef KNNCLASSIFIER_WORKINGTHREAD_HPP
#define KNNCLASSIFIER_WORKINGTHREAD_HPP
#include <pthread.h>
#include "Server/CLI.hpp"

class WorkingThread {
private:
    pthread_t id;
    char *buff;
    //CLI cli;
public:

    WorkingThread();

    int init();

    void start();

    void stop();

    void close();

    void setParams(char *buffer, CLI clientCli);

private:
    void* threadService();
    static void* threadFunc(void* arg);
};
#endif //KNNCLASSIFIER_WORKINGTHREAD_HPP
