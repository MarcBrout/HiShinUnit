//
// Created by Zenox on 11/29/2017.
//

#ifndef GOMOKU_MONTECARLOIA_HPP
#define GOMOKU_MONTECARLOIA_HPP

#include "Logic/Cell.hpp"
#include "Logic/Board.hpp"
#include "Logic/Position.hpp"
#include "Logic/AAI.hpp"

namespace ai {
    class MonteCarloIA : public AAI {
    public:
        MonteCarloIA();

        MonteCarloIA(MonteCarloIA const &monteCarloIA) = delete;

    private:
        void initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases, size_t round) override;
        void resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) override;
    };
}

#endif //GOMOKU_MONTECARLOIA_HPP
