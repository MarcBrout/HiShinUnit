//
// Created by Zenox on 11/27/2017.
//

#include <array>
#include <iostream>
#include "Checker.hpp"

Checker::Checker() = default;

CellState Checker::hasAWinner(const std::array<std::array<CellState, 19>, 19> &board)
{
    CellState final;

    std::cout << "IN WINNER FUNC" << std::endl;
    if ((final = checks(board)) == Empty)
        return final;
    std::cout << "IN WINNER FUNC OUT" << std::endl;
    return final;
}

CellState Checker::checks(const std::array<std::array<CellState, 19>, 19> &board)
{
    for (uint32_t y = 0; y < board.size(); ++y)
    {
        for (uint32_t x = 0; x < board[y].size(); ++x)
        {
            CellState tmp = board[y][x];
            if (tmp == Player1 || tmp == Player2)
            {
                std::cout << "LOOP : " << x << ", " << y << std::endl;
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

uint32_t Checker::checkWinRow(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    std::cout << "INTO DIA ROW : " << count << std::endl;
    for (count; count < 5; ++count)
    {
        std::cout << "COUNT ROW : " << count << std::endl;
        if ((count + x >= board[y].size()) || (board[y][x + count] != state))
            break;
    }
    std::cout << "OUT ROW : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkWinCol(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    std::cout << "INTO COL: " << count << std::endl;
    for (count; count < 5; ++count)
    {
        std::cout << "COUNT COL : " << count << std::endl;
        if ((count + y >= board.size()) || (board[y + count][x] != state))
            break;
    }
    std::cout << "OUT COL : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkWinDiaRight(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    std::cout << "INTO DIA RIGHT : " << count << std::endl;
    for (count; count < 5; ++count)
    {
        std::cout << "COUNT DIA RIGHT : " << count << std::endl;
        if ((count + x >= board[y].size()) || (count + y >= board.size()) || (board[y + count][x + count] != state))
            break;
    }
    std::cout << "OUT DIA RIGHT : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkWinDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    std::cout << "INTO DIA LEFT : " << count << std::endl;
    for (count; count < 5; ++count)
    {
        std::cout << "COUNT DIA LEFT : " << count << " => " << x << ", " << y << std::endl;
        if ((x - count < 0) || (y - count < 0) || (board[y - count][x - count] != state))
            break;
    }
    std::cout << "OUT DIA LEFT : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

bool Checker::checkInRowBefore(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return x - 1 >= 0 && board[y][x - 1] == Empty;
}

bool Checker::checkInRowAfter(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return x + 4 < board.size() && board[y][x + 4] == Empty;
}

bool Checker::checkInDiaRightAfter(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return (x + 4 < board.size() && y + 4 < board.size()) && board[y + 4][x + 4] == Empty;
}

bool Checker::checkInColBefore(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return y - 1 >= 0 && board[y - 1][x] == Empty;
}

bool Checker::checkInColAfter(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return y + 4 < board.size() && board[y + 4][x] == Empty;
}

bool Checker::checkInDiaLeftBefore(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return (x + 1 < board.size() && y - 1 >= 0) && board[y - 1][x + 1] == Empty;
}

bool Checker::checkInDiaLeftAfter(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return (x - 4 >= 0 && y + 4 < board.size()) && board[y + 4][x - 4] == Empty;
}

bool Checker::checkInDiaRightBefore(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y) const {
    return (x - 1 >= 0 && y - 1 >= 0) && board[y - 1][x - 1] == Empty;
}
