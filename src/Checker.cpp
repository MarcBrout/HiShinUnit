//
// Created by Zenox on 11/27/2017.
//

#include <array>
#include "Checker.h"

Checker::Checker() = default;

CellState Checker::hasAWinner(std::array<std::array<CellState, 19>, 19> &board)
{
    CellState final;

    if (((final = checkWinRow(board)) == Empty) &&
        ((final = checkWinCol(board)) == Empty) &&
        ((final = checkWinDiaRight(board)) == Empty) &&
        ((final = checkWinDiaLeft(board)) == Empty))
        return Empty;
    return final;
}

CellState Checker::checkWinRow(std::array<std::array<CellState, 19>, 19> &board)
{
    for (uint32_t y = 0; y < board.size(); ++y)
    {
        for (int32_t x = 0; x < board[y].size(); ++x)
        {
            CellState tmp = board[y][x];
            if (tmp == Player1 || tmp == Player2)
            {
                uint32_t count = 1;
                for (count; count < 5; ++count)
                {
                    if ((count + x >= board[y].size()) || (board[y][x + count] != tmp))
                        break;
                }
                if (count == 5)
                    return tmp;
            }
        }
    }
    return Empty;
}

CellState Checker::checkWinCol(std::array<std::array<CellState, 19>, 19> &board)
{
    for (uint32_t y = 0; y < board.size(); ++y)
    {
        for (uint32_t x = 0; x < board[y].size(); ++x)
        {
            CellState tmp = board[y][x];
            if (tmp == Player1 || tmp == Player2)
            {
                uint32_t count = 1;
                for (count; count < 5; ++count)
                {
                    if ((count + y >= board.size()) || (board[y + count][x] != tmp))
                        break;
                }
                if (count == 5)
                    return tmp;
            }
        }
    }
    return Empty;
}

CellState Checker::checkWinDiaRight(std::array<std::array<CellState, 19>, 19> &board)
{
    for (uint32_t y = 0; y < board.size(); ++y)
    {
        for (uint32_t x = 0; x < board[y].size(); ++x)
        {
            CellState tmp = board[y][x];
            if (tmp == Player1 || tmp == Player2)
            {
                uint32_t count = 1;
                for (count; count < 5; ++count)
                {
                    if ((count + x >= board[y].size()) || (count + y >= board.size()) || (board[y + count][x + count] != tmp))
                        break;
                }
                if (count == 5)
                    return tmp;
            }
        }
    }
    return Empty;
}

CellState Checker::checkWinDiaLeft(std::array<std::array<CellState, 19>, 19> &board)
{
    for (uint32_t y = 0; y < board.size(); ++y)
    {
        for (uint32_t x = 0; x < board[y].size(); ++x)
        {
            CellState tmp = board[y][x];
            if (tmp == Player1 || tmp == Player2)
            {
                uint32_t count = 1;
                for (count; count < 5; ++count)
                {
                    if ((x - count < 0) || (y - count < 0) || (board[y - count][x - count] != tmp))
                        break;
                }
                if (count == 5)
                    return tmp;
            }
        }
    }
    return Empty;
}