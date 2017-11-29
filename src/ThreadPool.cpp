//
// Created by Pierre Bougon on 28/11/2017.
//

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(unsigned int nbThreads)
        : threads(), todoCases(), doneCases(), state(), running(true), condvar(), mutex()
{
    for (unsigned int i = 0; i < nbThreads; ++i)
    {
        // TODO repair this shit
       // threads.push_back(std::thread(&ThreadPool::threadWorkflow, this, i));
       state.push_back(ThreadState::sleeping);
    }
    running = true;
}

bool ThreadPool::addCase(std::unique_ptr<ai::AICase> task)
{
    mutex.lock();
    todoCases.push(std::move(task));
    mutex.unlock();
    condvar.notify_one();
    return true;
}

void ThreadPool::stop()
{
    running = false;
    condvar.notify_all();
    for (std::thread &th : threads)
        th.join();
    threads.clear();
}

std::unique_ptr<ai::AICase> ThreadPool::getCaseDone()
{
    mutex.lock();
    std::unique_ptr<ai::AICase> aiCase = std::move(doneCases.front());
    doneCases.pop();
    mutex.unlock();
    return std::move(aiCase);
}

void ThreadPool::threadWorkflow(unsigned int id)
{
    while (running)
    {

        // Check if we have done all the tasks to do
        if (todoCases.empty())
        {
            // Wait until we rcv notification
            state[id] = ThreadState::sleeping;
            std::unique_lock<std::mutex> ulock(mutex);
            condvar.wait(ulock);
        }

        // If ThreadPool is down we stop the thread
        if (!running)
            break;

        state[id] = ThreadState::working;
        mutex.lock();
        if (todoCases.empty())
            continue;
        std::unique_ptr<ai::AICase> aiCase = std::move(todoCases.front());
        todoCases.pop();
        mutex.unlock();

        // Process the task
        //aiCase.ntry(1000);

        // Add task to doneTasks queue
        mutex.lock();
        doneCases.push(std::move(aiCase));
        mutex.unlock();
    }
}

std::deque<std::unique_ptr<ai::AICase>> ThreadPool::getCasesDone(int round) {
    std::deque<std::unique_ptr<ai::AICase>> out;

    mutex.lock();
    while (!doneCases.empty()) {
        if ((*doneCases.front()).getRound() == round) {
            out.push_back(std::move(doneCases.front()));
        }
        doneCases.pop();
    }
    mutex.unlock();
    return out;
}
