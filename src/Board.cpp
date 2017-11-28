//
// Created by Zenox on 11/27/2017.
//

#include "Board.hpp"

Board::Board() : checker()
{
    board = {{Empty}};
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
    for (std::array<CellState, 19> &y : board) {
        for (CellState &state : y) {
            state = Empty;
        }
    }
}

const std::array<std::array<CellState, 19>, 19> &Board::getBoard() const {
    return board;
}
