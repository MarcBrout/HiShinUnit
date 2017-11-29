//
// Created by Zenox on 11/27/2017.
//

#include <iostream>
#include "Board.hpp"

Board::Board() : checker()
{
    for (std::array<CellState, 19> &line : board) {
        for (CellState &cell : line) {
            cell = Empty;
        }
    }
}

Board::Board(Board const &board)
{
    this->board = board.board;
}

void Board::setCellState(uint32_t posY, uint32_t posX, CellState state)
{
    board[posY][posX] = state;
}

CellState Board::getCellState(uint32_t posY, uint32_t posX) const
{
    return board[posY][posX];
}

void Board::reset()
{
    board = {};
    for (std::array<CellState, 19> &y : board) {
        for (CellState &state : y) {
            state = Empty;
        }
    }
}

const std::array<std::array<CellState, 19>, 19> &Board::getBoard() const {
    return board;
}

std::array<CellState, 19> &Board::operator[](uint32_t y) {
    return board[y];
}

const std::array<CellState, 19> &Board::operator[](uint32_t y) const {
    return board[y];
}

Board &Board::operator=(Board &board) {
    if (&board != this)
    {
        this->checker = board.checker;
        this->board = board.board;
    }
    return *this;
}

Checker Board::getChecker() const {
    return Checker();
}

bool Board::isFill() {
    for (std::array<CellState, 19> &y : board) {
        for (CellState &state : y) {
            if (state == Empty)
                return false;
        }
    }
    return true;
}
