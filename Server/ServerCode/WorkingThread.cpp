#include "WorkingThread.hpp"


WorkingThread::WorkingThread() {}

int WorkingThread::init() {
    threadFunc(this);
    int res = pthread_create(&id, NULL,threadFunc, NULL);
    if(res == -1) {
        perror("pthread_create failed");
        return -1;
       }
    return 0;
}

void WorkingThread::start() {

}

void WorkingThread::stop(){}

void WorkingThread::close(){}

void WorkingThread::setParams(char *buffer, CLI clientCli){}

void* WorkingThread::threadService()
{

}
//static
void* WorkingThread::threadFunc(void* arg) {
    WorkingThread* thr = (WorkingThread*)arg;
    return thr->threadService();
}