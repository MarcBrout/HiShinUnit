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

    //std::cout << "IN WINNER FUNC" << std::endl;
    if ((final = checks(board)) == Empty)
        return final;
  //  std::cout << "IN WINNER FUNC OUT" << std::endl;
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
      //          std::cout << "LOOP : " << x << ", " << y << std::endl;
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

uint32_t Checker::checkCanWinRow(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    CellState enemy = (state == Player2) ? Player1 : Player2;
    bool alreadyOneEmpty = false;
    //std::cout << "INTO DIA ROW : " << count << std::endl;
    for (count; count < 5; ++count)
    {
        //  std::cout << "COUNT ROW : " << count << std::endl;
        if ((count + x >= board[y].size()) || (board[y][x + count] == enemy))
            break;
        if (board[y][x + count] == Empty)
        {
            if (alreadyOneEmpty)
                return static_cast<uint32_t>(count);
            alreadyOneEmpty = true;
        }
    }
    if (count == 4 && !alreadyOneEmpty)
        count++;
    //std::cout << "OUT ROW : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkCanWinCol(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    bool alreadyOneEmpty = false;
    CellState enemy = (state == Player2) ? Player1 : Player2;
    //std::cout << "INTO COL: " << count << std::endl;
    for (count; count < 5; ++count)
    {
        //  std::cout << "COUNT COL : " << count << std::endl;
        if ((count + y >= board.size()) || (board[y + count][x] == enemy))
            break;

        if (board[y + count][x] == Empty)
        {
            if (alreadyOneEmpty)
                return static_cast<uint32_t>(count);
            alreadyOneEmpty = true;
        }
    }
    if (count == 4 && !alreadyOneEmpty)
        count++;
    //std::cout << "OUT COL : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkCanWinDiaRight(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    bool alreadyOneEmpty = false;
    CellState enemy = (state == Player2) ? Player1 : Player2;
    //std::cout << "INTO DIA RIGHT : " << count << std::endl;
    for (count; count < 5; ++count)
    {
        //  std::cout << "COUNT DIA RIGHT : " << count << std::endl;
        if ((count + x >= board[y].size()) || (count + y >= board.size()) || (board[y + count][x + count] == enemy))
            break;
        if (board[y + count][x + count] == Empty)
        {
            if (alreadyOneEmpty)
                return static_cast<uint32_t>(count);
            alreadyOneEmpty = true;
        }
    }
    if (count == 4 && !alreadyOneEmpty)
        count++;
    //std::cout << "OUT DIA RIGHT : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkCanWinDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    bool alreadyOneEmpty = false;
    CellState enemy = (state == Player2) ? Player1 : Player2;

    //std::cout << "INTO DIA LEFT : " << count << std::endl;
    for (count; count < 5; ++count)
    {
        //  std::cout << "COUNT DIA LEFT : " << count << " => " << x << ", " << y << std::endl;
        if ((x - count < 0) || (y + count >= board.size()) || (board[y + count][x - count] == enemy))
            break;
        if (board[y + count][x - count] == Empty)
        {
            if (alreadyOneEmpty)
                return static_cast<uint32_t>(count);
            alreadyOneEmpty = true;
        }
    }
    if (count == 4 && !alreadyOneEmpty)
        count++;
    //std::cout << "OUT DIA LEFT : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkWinRow(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;

    //std::cout << "INTO DIA ROW : " << count << std::endl;
    for (count; count < 5; ++count)
    {
      //  std::cout << "COUNT ROW : " << count << std::endl;
        if ((count + x >= board[y].size()) || (board[y][x + count] != state))
            break;
    }
    //std::cout << "OUT ROW : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkWinCol(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    //std::cout << "INTO COL: " << count << std::endl;
    for (count; count < 5; ++count)
    {
      //  std::cout << "COUNT COL : " << count << std::endl;
        if ((count + y >= board.size()) || (board[y + count][x] == state))
            break;
    }
    //std::cout << "OUT COL : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkWinDiaRight(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    //std::cout << "INTO DIA RIGHT : " << count << std::endl;
    for (count; count < 5; ++count)
    {
      //  std::cout << "COUNT DIA RIGHT : " << count << std::endl;
        if ((count + x >= board[y].size()) || (count + y >= board.size()) || (board[y + count][x + count] == state))
            break;
    }
    //std::cout << "OUT DIA RIGHT : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

uint32_t Checker::checkWinDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, CellState state) const
{
    int32_t count = 1;
    //std::cout << "INTO DIA LEFT : " << count << std::endl;
    for (count; count < 5; ++count)
    {
      //  std::cout << "COUNT DIA LEFT : " << count << " => " << x << ", " << y << std::endl;
        if ((x - count < 0) || (y + count >= board.size()) || (board[y + count][x - count] != state))
            break;
    }
    //std::cout << "OUT DIA LEFT : " << count << std::endl;
    return static_cast<uint32_t>(count);
}

bool Checker::checkInRow(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const {
    if (pos < 0)
        return x + pos >= 0 && board[y][x + pos] == Empty;
    return x + pos < board.size() && board[y][x + pos] == Empty;
}

bool Checker::checkInCol(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const {
    if (pos < 0)
        return y + pos >= 0 && board[y + pos][x] == Empty;
    return y + pos < board.size() && board[y + pos][x] == Empty;
}

bool Checker::checkInDiaRight(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const {
    if (pos < 0)
        return (x + pos >= 0 && y + pos >= 0) && board[y + pos][x + pos] == Empty;
    return (x + pos < board.size() && y + pos < board.size()) && board[y + pos][x + pos] == Empty;
}

bool Checker::checkInDiaLeft(const std::array<std::array<CellState, 19>, 19> &board, int32_t x, int32_t y, int32_t pos) const {
    if (pos < 0)
        return (x - pos < board.size() && y + pos >= 0) && board[y + pos][x - pos] == Empty;
    return (x - pos >= 0 && y + pos < board.size()) && board[y + pos][x - pos] == Empty;
}