//
// Created by Zenox on 11/29/2017.
//

#ifndef GOMOKU_MONTECARLOIA_HPP
#define GOMOKU_MONTECARLOIA_HPP

#include "Cell.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "AAI.hpp"

class MonteCarloIA  : AAI {
private:
    Board board;
    Checker checker;
public:
    MonteCarloIA() = delete;
    explicit MonteCarloIA(Board board1);
    MonteCarloIA(MonteCarloIA const& monteCarloIA) = delete;

private:
    void initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases) override;

    void resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) override;
//    void getIaPlay(Position &outPos);
};


#endif //GOMOKU_MONTECARLOIA_HPP
