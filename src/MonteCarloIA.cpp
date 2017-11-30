//
// Created by Zenox on 11/29/2017.
//

#include "MonteCarloIA.hpp"
#include "MonteCarloCase.hpp"

MonteCarloIA::MonteCarloIA() : AAI()
{
}

void
MonteCarloIA::initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases, size_t round) {
    Position curMax;
    // Count is the max probality value of the cell
    uint32_t count = 0;

    // Tmp will receive the return of monteCarlo algo and will be compared with count
    uint32_t tmp = 0;

    // looking for an Empty cell which i'll launch the monteCarlo recursive
    for (uint32_t y = 0; y < board.getBoard().size(); ++y)
    {
        for (uint32_t x = 0; x < board.getBoard()[y].size(); ++x)
        {
            if (board[y][x] == Empty) {
                outCases.push_back(
                        std::make_unique<ai::MonteCarloCase>(board, x, y, 0)
                );
            }
        }
    }
}

void MonteCarloIA::resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) {
    double max = -1.0;

    for (auto const &oneCase : casesDone)
    {
        if (max < (*oneCase).getWeight())
        {
            max = (*oneCase).getWeight();
            posOut = (*oneCase).getPos();
        }
    }
}
