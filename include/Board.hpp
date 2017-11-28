//
// Created by Zenox on 11/27/2017.
//

#ifndef GOMOKU_BOARD_H
#define GOMOKU_BOARD_H

#include "Cell.hpp"
#include "Checker.hpp"
#include <array>

class Board {
public:
    Board();
    Board(Board const& board);
    Board(std::array<std::array<CellState, 19>, 19> &array) = delete;

    void setCellState(uint32_t y, uint32_t x, CellState state);
    CellState getCellState(uint32_t y, uint32_t x) const;

    const std::array<std::array<CellState, 19>, 19> &getBoard() const;

    void reset();
    std::array<CellState, 19> &operator[](uint32_t y);

private:
    Checker checker;
    std::array<std::array<CellState, 19>, 19> board = {{}};
};

#endif //GOMOKU_BOARD_H
