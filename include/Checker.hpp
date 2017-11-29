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
    uint32_t checkWinRow(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state) const;
    uint32_t checkWinCol(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state) const;
    uint32_t checkWinDiaRight(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state) const;
    uint32_t checkWinDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state) const;

    bool checkInRowBefore(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
    bool checkInRowAfter(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
    bool checkInColBefore(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
    bool checkInColAfter(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
    bool checkInDiaLeftBefore(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
    bool checkInDiaLeftAfter(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
    bool checkInDiaRightBefore(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
    bool checkInDiaRightAfter(const std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y) const;
};

#endif //GOMOKU_CHECKER_H
