//
// Created by Zenox on 11/27/2017.
//

#ifndef GOMOKU_CHECKER_H
#define GOMOKU_CHECKER_H

#include "Cell.h"
#include <array>

class Checker {
public:
    Checker();
    CellState hasAWinner(std::array<std::array<CellState, 19>, 19> &);

private:
    CellState checkWinRow(std::array<std::array<CellState, 19>, 19> &);
    CellState checkWinCol(std::array<std::array<CellState, 19>, 19> &);
    CellState checkWinDiaRight(std::array<std::array<CellState, 19>, 19> &);
    CellState checkWinDiaLeft(std::array<std::array<CellState, 19>, 19> &);
};

#endif //GOMOKU_CHECKER_H
