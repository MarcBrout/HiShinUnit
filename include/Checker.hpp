//
// Created by Zenox on 11/27/2017.
//

#ifndef GOMOKU_CHECKER_H
#define GOMOKU_CHECKER_H

#include "Cell.hpp"
#include <array>

class Checker {
public:
    Checker();
    CellState hasAWinner(std::array<std::array<CellState, 19>, 19> &);

private:
    CellState checks(std::array<std::array<CellState, 19>, 19> &);
    uint32_t checkWinRow(std::array<std::array<CellState, 19>, 19> &, uint32_t, uint32_t, CellState);
    uint32_t checkWinCol(std::array<std::array<CellState, 19>, 19> &, uint32_t, uint32_t, CellState);
    uint32_t checkWinDiaRight(std::array<std::array<CellState, 19>, 19> &, uint32_t, uint32_t, CellState);
    uint32_t checkWinDiaLeft(std::array<std::array<CellState, 19>, 19> &, uint32_t, uint32_t, CellState);
};

#endif //GOMOKU_CHECKER_H
