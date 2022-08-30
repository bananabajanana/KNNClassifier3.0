#ifndef KNNCLASSIFIER_THREADPOOL_HPP
#define KNNCLASSIFIER_THREADPOOL_HPP
class WorkingThread;


class ThreadPool {
private:
    enum {THREADS_NUM = 16};
    WorkingThread* threads_arr[THREADS_NUM];
    char busy_arr[THREADS_NUM];
public:
    /**
     *
     */
    ThreadPool();
    /**
     * opens the pool
     * @return success
     */
    bool init();
    /**
     * closes the pool.
     */
    void close();
    /**
     * gets thread for processing.
     * @return thread id.
     */
    WorkingThread* getThread();
    /**
     * returns the thread.
     */
    void returnThread(WorkingThread *thread);
};


#endif //KNNCLASSIFIER_THREADPOOL_HPP
