//
// Created by Zenox on 11/29/2017.
//

#include "MonteCarloIA.hpp"
#include "MonteCarloCase.hpp"

static const unsigned int max_threads = std::thread::hardware_concurrency();

MonteCarloIA::MonteCarloIA() : AAI(max_threads > 0 ? max_threads : 4, 4500)
{
}

void MonteCarloIA::initializeCases(Board const &board,
                                   std::deque<std::unique_ptr<ai::AICase>> &outCases,
                                   size_t round)
{
    if (board.isEmpty())
    {
        outCases.push_back(
                std::make_unique<ai::MonteCarloCase>(board, board.getSize(0) / 2,
                                                     board.getSize() / 2,
                                                     round));
        return ;
    }

    // looking for an Empty cell which i'll launch the monteCarlo recursive
    for (uint32_t y = 0; y < board.getSize(); ++y)
    {
        for (uint32_t x = 0; x < board.getSize(y); ++x)
        {
            if (canIProcess(board, x, y)) {
                outCases.push_back(
                        std::make_unique<ai::MonteCarloCase>(board, x, y, round)
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

bool MonteCarloIA::canIProcess(Board const &board, int32_t x, int32_t y) const {
    if (board[y][x] == Empty) {
        if ((x - 1) >= 0 && board[y][x - 1] != Empty)
            return true;
        if ((y - 1) > 0 && board[y - 1][x] != Empty)
            return true;
        if ((x + 1) < board.getSize(static_cast<uint32_t >(y)) && board[y][x + 1] != Empty)
            return true;
        if ((y + 1) < board.getSize() && board[y + 1][x] != Empty)
            return true;
        if ((x - 1) >= 0 && (y - 1) >= 0 && board[y - 1][x - 1] != Empty)
            return true;
        if ((x + 1) < board.getSize(static_cast<uint32_t >(y)) && (y - 1) >= 0 && board[y - 1][x + 1] != Empty)
            return true;
        if ((x + 1) < board.getSize(static_cast<uint32_t >(y)) && (y + 1) < board.getSize(static_cast<uint32_t >(y)) &&
                board[y + 1][x + 1] != Empty)
            return true;
        if ((x - 1) >= 0 && (y + 1) < board.getSize(static_cast<uint32_t >(y)) && board[y + 1][x - 1] != Empty)
            return true;
    }
    return false;
}
