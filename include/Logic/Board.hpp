//
// Created by Zenox on 11/27/2017.
//

#ifndef GOMOKU_BOARD_H
#define GOMOKU_BOARD_H

#include "Cell.hpp"
#include "MonteCarlo/Checker.hpp"
#include <array>

/**
 * Class representing a 2d board of 19 x 19 cells
 */
class Board {
public:
    Board();
    Board(Board const& board);
    Board &operator=(Board const &board);

    // Getters and setters
    void setCellState(uint32_t x, uint32_t y, CellState state);
    CellState getCellState(uint32_t x, uint32_t y) const;
    uint32_t getSize() const;
    uint32_t getSize(uint32_t y) const;
    const std::array<std::array<CellState, 19>, 19> &getBoard() const;
    Checker getChecker() const;

    void reset();
    bool isFill();
    bool isEmpty() const;

    std::array<CellState, 19> &operator[](uint32_t y);
    const std::array<CellState, 19> &operator[](uint32_t y) const;

private:
    Checker                                     checker;
    std::array<std::array<CellState, 19>, 19>   board;
    bool                                        empty;

    // Delete constructors and operators
public:
    Board(Board &&) = delete;
    Board(std::array<std::array<CellState, 19>, 19> &array) = delete;
    Board &operator=(Board &&) = delete;
};

#endif //GOMOKU_BOARD_H
