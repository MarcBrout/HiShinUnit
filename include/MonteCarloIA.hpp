//
// Created by Zenox on 11/29/2017.
//

#ifndef GOMOKU_MONTECARLOIA_HPP
#define GOMOKU_MONTECARLOIA_HPP

#include "Cell.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "AAI.hpp"

class MonteCarloIA : public AAI {
public:
    MonteCarloIA();
    MonteCarloIA(MonteCarloIA const& monteCarloIA) = delete;

private:
    void initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases, size_t round) override;

    void resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) override;
};


#endif //GOMOKU_MONTECARLOIA_HPP
