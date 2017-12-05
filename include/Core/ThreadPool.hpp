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
#include "Logic/AICase.hpp"
#include "ThreadState.hpp"

namespace ai {
    /**
     * This ThreadPool has threads running and waiting for cases to process.
     * Once the case is process, it is resent to the out queue for further resolving.
     */
    class ThreadPool {
    public:
        /**
         * Constructor
         * @param nbThreads Number of threads to be running and waiting
         */
        explicit ThreadPool(unsigned int nbThreads);
        ~ThreadPool();

        /**
         * Pushes a case to be processed by the workers.
         * This method is thread safe.
         * @param task to be processed
         * @return true once the case has been added
         */
        bool addCase(std::unique_ptr<ai::AICase> task);

        /**
         * Notify the threads to stop, and wait for it
         */
        void stop();

        /**
         * Get the front case done
         * @return the case using move semantics
         */
        std::unique_ptr<ai::AICase> getCaseDone();

        /**
         * Get all cases processed so far for the current round
         * @param round
         * @return the cases of the round using the move semantics
         */
        std::deque<std::unique_ptr<ai::AICase>> getCasesDone(int round);

    protected:
        std::vector<std::thread> threads;
        std::queue<std::unique_ptr<ai::AICase>> todoCases;
        std::queue<std::unique_ptr<ai::AICase>> doneCases;
        std::vector<ThreadState> state;
        std::atomic<bool> running;
        std::condition_variable condvar;
        std::mutex mutex;

        /**
         * Thread worker main method
         * @param id of the thread
         */
        void threadWorkflow(unsigned int id);

        // Deleted constructors or operators
    public:
        ThreadPool() = delete;
        ThreadPool(ThreadPool const&) = delete;
        ThreadPool(ThreadPool &&) = delete;
        ThreadPool &operator=(ThreadPool const&) = delete;
        ThreadPool &operator=(ThreadPool &&) = delete;
    };
}

#endif // !GOMOKU_THREADPOOL_HPP_
