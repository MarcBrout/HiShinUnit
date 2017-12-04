//
// Created by 53818 on 29/11/2017.
//

#include <chrono>
#include <iostream>
#include "Logic/AAI.hpp"

AAI::AAI(unsigned int threadCount, unsigned int timeLimit) :
        threadPool(threadCount),
        cases(),
        timeOut(timeLimit) {
}

void AAI::getAIPlay(Board const& board, size_t round, Position &posOut) {
    initializeCases(board, cases, round);

    while (!cases.empty()) {
        threadPool.addCase(std::move(cases.front()));
        cases.pop_front();
    }

    //std::cout << "Go to the BED" << std::endl;

    // Stop the main thread for timeOut milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(timeOut));

    //std::cout << "WAKE UP" << std::endl;

    std::deque<std::unique_ptr<ai::AICase>> results = threadPool.getCasesDone(round);
    //std::cout << "SIZE = " << results.size() << std::endl;

    resolve(results, posOut);
}

void AAI::setTimeOut(unsigned int timeLimit) {
     timeOut = timeLimit;
}

void AAI::stop()
{
    threadPool.stop();
}
