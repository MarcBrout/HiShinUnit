//
// Created by Zenox on 11/29/2017.
//

#ifndef GOMOKU_MONTECARLOIA_HPP
#define GOMOKU_MONTECARLOIA_HPP

#include "Cell.hpp"
#include "Board.hpp"
#include "Position.hpp"

class MonteCarloIA {

private:
    Board board;

public:
    MonteCarloIA() = delete;
    explicit MonteCarloIA(Board board1);
    MonteCarloIA(MonteCarloIA const& monteCarloIA) = delete;

    void getIaPlay(Position &outPos);

private:
    bool canIWin(Board &myBoard, Position &out, CellState player);
    bool enemyCanWin(Board &myBoard, Position &out, CellState player );
    CellState recurs(Board &board, uint32_t x, uint32_t y, CellState state);
    uint32_t monteCarlo(uint32_t x, uint32_t y);
};


#endif //GOMOKU_MONTECARLOIA_HPP
