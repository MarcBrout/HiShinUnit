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
    for (uint32_t y = 0 ; y < board.size(); y++)
    {
        for (uint32_t x = 0; x < board[y].size(); x++)
        {
            board[y][x] = Empty;
        }
    }
}
