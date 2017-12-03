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
    CellState hasAWinner(const std::array<std::array<CellState, 19>, 19> &board);
    CellState checks(const std::array<std::array<CellState, 19>, 19> &board);
    uint32_t checkWinRow(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;
    uint32_t checkWinCol(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;
    uint32_t checkWinDiaRight(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;
    uint32_t checkWinDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;

    uint32_t checkCanWinRow(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;
    uint32_t checkCanWinCol(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;
    uint32_t checkCanWinDiaRight(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;
    uint32_t checkCanWinDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const;

    bool checkInRow(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const;
    bool checkInCol(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const;
    bool checkInDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const;
    bool checkInDiaRight(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const;
};

#endif //GOMOKU_CHECKER_H
