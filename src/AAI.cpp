//
// Created by 53818 on 29/11/2017.
//

#include <chrono>
#include "AAI.hpp"

AAI::AAI(unsigned int threadCount, unsigned int timeLimit) :
        threadPool(threadCount),
        cases(),
        timeOut(timeLimit) {
}

void AAI::getAIPlay(Board const& board, int round, Position &posOut) {
    initializeCases(board, cases);

    while (!cases.empty()) {
        threadPool.addCase(std::move(cases.front()));
        cases.pop_front();
    }

    // Stop the main thread for timeOut milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(timeOut));

    std::deque<std::unique_ptr<ai::AICase>> results = threadPool.getCasesDone(round);

    resolve(results, posOut);
}

void AAI::setTimeOut(unsigned int timeLimit) {
     timeOut = timeLimit;
}
