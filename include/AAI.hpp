//
// Created by 53818 on 29/11/2017.
//

#ifndef GOMOKU_AAI_HPP
#define GOMOKU_AAI_HPP

#include <memory>
#include "ThreadPool.hpp"
#include "AICase.hpp"
#include "Position.hpp"
#include "Board.hpp"

/**
 * This is the abstract representation of an AI.
 * It has ownership on its own ThreadPool and is responsible for running the algorithm through AICase.
 */
class AAI {
public:
    /**
     * Only construtor authorized.
     * @param threadCount : number of threads used to resolve the cases
     * @param timeLimit : timeout before the AI retrieve the cases resolved
     */
    AAI(unsigned int threadCount = 20, unsigned int timeLimit = 4000);
    AAI(AAI const&) = delete;
    AAI(AAI &&) = delete;

    /**
     * This function will push the items first initialized from the initialize function
     * into the threadpool for their resolution.
     * After sleeping timeOut milliseconds, it will wake up and get the cases done.
     * It will call the resolve method to return the winning move.
     * @param board : current state of the board
     * @param round : round count used to discard useless cases
     * @param posOut : winning move decided by the AAI
     */
    void getAIPlay(Board const &board, size_t round, Position &posOut);

    /**
     * Set the the time in milliseconds the threadpool should be working, the result will be
     * returned when the time limit is reached.
     * @param timeLimit
     */
    void setTimeOut(unsigned int timeOut);

    /**
     * Call the AI to cease working and stop all threads
     */
    void stop();

protected:
    ThreadPool threadPool;
    std::deque<std::unique_ptr<ai::AICase>> cases;
    unsigned int timeOut;

    /**
    * The user shall create, initialize and push his AICases in the outCases vector.
    * @param outCases : AICases that will be pushed into the threadpool
    */
    virtual void initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases, size_t round) = 0;

    /**
     * Method used to choose the best AICase from the resolved ones.
     * @param casesDone : resolved AICases
     */
    virtual void resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) = 0;
};


#endif //GOMOKU_AAI_HPP
