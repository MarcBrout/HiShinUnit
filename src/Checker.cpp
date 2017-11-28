//
// Created by Zenox on 11/27/2017.
//

#include <array>
#include "Checker.h"

Checker::Checker() = default;

CellState Checker::hasAWinner(std::array<std::array<CellState, 19>, 19> &board)
{
    CellState final;

    if ((final = checks(board)) == Empty)
        return final;
    return final;
}

CellState Checker::checks(std::array<std::array<CellState, 19>, 19> &board)
{
    for (uint32_t y = 0; y < board.size(); ++y)
    {
        for (uint32_t x = 0; x < board[y].size(); ++x)
        {
            CellState tmp = board[y][x];
            if (tmp == Player1 || tmp == Player2)
            {
                if ((checkWinRow(board, x, y, tmp) == 5) ||
                    (checkWinCol(board, x, y, tmp) == 5) ||
                    (checkWinDiaRight(board, x, y, tmp) == 5) ||
                    (checkWinDiaLeft(board, x, y, tmp) == 5))
                    return tmp;
            }
        }
    }
    return Empty;
}

uint32_t Checker::checkWinRow(std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state)
{
    uint32_t count = 1;
    for (count; count < 5; ++count)
    {
        if ((count + x >= board[y].size()) || (board[y][x + count] != state))
            break;
    }
    return count;
}

uint32_t Checker::checkWinCol(std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state)
{
    uint32_t count = 1;
    for (count; count < 5; ++count)
    {
        if ((count + y >= board.size()) || (board[y + count][x] != state))
            break;
    }
    return count;
}

uint32_t Checker::checkWinDiaRight(std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state)
{
    uint32_t count = 1;
    for (count; count < 5; ++count)
    {
        if ((count + x >= board[y].size()) || (count + y >= board.size()) || (board[y + count][x + count] != state))
            break;
    }
    return count;
}

uint32_t Checker::checkWinDiaLeft(std::array<std::array<CellState, 19>, 19> &board, uint32_t x, uint32_t y, CellState state)
{
    uint32_t count = 1;
    for (count; count < 5; ++count)
    {
        if ((x - count < 0) || (y - count < 0) || (board[y - count][x - count] != state))
            break;
    }
    return count;
}