//
// Created by Zenox on 11/27/2017.
//

#ifndef GOMOKU_BOARD_H
#define GOMOKU_BOARD_H

#include "Cell.h"
#include "Checker.h"
#include <array>

class Board {
public:
    Board();
    Board(Board const&);
    Board(std::array<std::array<CellState, 19>, 19> &) = delete;

    void setCellState(uint32_t, uint32_t, CellState);
    CellState &getCellState(uint32_t, uint32_t) const;
    void reset();

private:
    Checker checker;
    std::array<std::array<CellState, 19>, 19> board;
};


#endif //GOMOKU_BOARD_H
