//
// Created by Pierre Bougon on 28/11/2017.
//

#ifndef GOMOKU_THREADPOOL_HPP_
#define GOMOKU_THREADPOOL_HPP_

#include <windows.h>
#include <vector>
#include <condition_variable>
#include <thread>
#include <queue>
#include <atomic>
#include "AICase.hpp"
#include "ThreadState.hpp"

class ThreadPool
{
public:
    ThreadPool() = delete;
    explicit ThreadPool(unsigned int nbThreads);

    bool        addTask(std::unique_ptr<AICase> task);
    void        stop();
    std::unique_ptr<AICase> getCaseDone();
    std::deque<std::unique_ptr<AICase>> getCasesDone(int round);

protected:
    std::vector<std::thread>                    threads;
    std::queue<std::unique_ptr<AICase>>         todoCases;
    std::queue<std::unique_ptr<AICase>>         doneCases;
    std::vector<ThreadState>                    state;
    std::atomic<bool>                           running;
    std::condition_variable                     condvar;
    std::mutex                                  mutex;

    void threadWorkflow(unsigned int id);
};


#endif // !GOMOKU_THREADPOOL_HPP_
