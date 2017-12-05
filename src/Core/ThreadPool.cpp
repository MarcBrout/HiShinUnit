//
// Created by Pierre Bougon on 28/11/2017.
//

#include <iostream>
#include "Core/ThreadPool.hpp"

namespace ai {
    ThreadPool::ThreadPool(unsigned int nbThreads)
            : threads(), todoCases(), doneCases(), state(), running(true), condvar(), mutex() {
        for (unsigned int i = 0; i < nbThreads; ++i) {
            // TODO repair this shit
            threads.emplace_back(std::thread(&ThreadPool::threadWorkflow, this, i));
            state.push_back(ThreadState::sleeping);
        }
        running = true;
    }

    bool ThreadPool::addCase(std::unique_ptr<ai::AICase> task) {
        mutex.lock();
        todoCases.push(std::move(task));
        mutex.unlock();
        condvar.notify_one();
        return true;
    }

    void ThreadPool::stop() {
        running = false;
        condvar.notify_all();

        bool hasAllThreadJoined = false;
        while (!hasAllThreadJoined) {
            hasAllThreadJoined = true;
            for (std::thread &th : threads) {
                if (th.joinable()) {
                    th.join();
                } else {
                    hasAllThreadJoined = false;
                }
            }
        }
        threads.clear();
    }

    std::unique_ptr<ai::AICase> ThreadPool::getCaseDone() {
        mutex.lock();
        std::unique_ptr<ai::AICase> aiCase = std::move(doneCases.front());
        doneCases.pop();
        mutex.unlock();
        return std::move(aiCase);
    }

    void ThreadPool::threadWorkflow(unsigned int id) {
        while (running) {
            // std::cout << "thread " << id << " started here " << std::endl;
            // Check if we have done all the tasks to do
            mutex.lock();
            if (todoCases.empty()) {
                // Wait until we rcv notification
                //state[id] = ThreadState::sleeping;
                mutex.unlock();
                std::unique_lock<std::mutex> ulock(mutex);
                condvar.wait(ulock);
            } else {
                mutex.unlock();
            }

            //std::cout << "thread " << id << " run here " << std::endl;
            // If ThreadPool is down we stop the thread
            if (!running)
                break;

            mutex.lock();
            //state[id] = ThreadState::working;
            if (todoCases.empty()) {
                mutex.unlock();
                continue;
            }
            std::unique_ptr<ai::AICase> aiCase = std::move(todoCases.front());
            todoCases.pop();
            //std::cout << "Cases to proceed: " << todoCases.size() << std::endl;
            //std::cout << "Case: " << (*aiCase).getPos().toString() << std::endl;
            mutex.unlock();

            // Process the task
            (*aiCase).process();
            //  std::cout << "thread " << id << " reached here " << std::endl;

            // Add task to doneTasks queue
            mutex.lock();
            doneCases.push(std::move(aiCase));
            mutex.unlock();
        }
    }

    std::deque<std::unique_ptr<ai::AICase>> ThreadPool::getCasesDone(int round) {
        std::deque<std::unique_ptr<ai::AICase>> out;

        mutex.lock();
        //std::cout << "STARTING TO REMOVE ROUND  : " << round << std::endl;
        while (!doneCases.empty()) {
            //std::cout << "object round = " << doneCases.front()->getRound() << std::endl;
            if ((*doneCases.front()).getRound() == round) {
                out.push_back(std::move(doneCases.front()));
            }
            doneCases.pop();
        }
        // std::cout << "ALL CASES TAKEN : " << out.size() << std::endl;
        mutex.unlock();
        return out;
    }
}