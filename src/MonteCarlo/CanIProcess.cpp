//
// Created by Zenox on 12/4/2017.
//

#include "MonteCarlo/CanIProcess.hpp"

bool  canIProcess(Board const &board, int32_t x, int32_t y) {
    if (board[y][x] == Empty) {
        if ((x - 1) >= 0 && board[y][x - 1] != Empty)
            return true;
        if ((y - 1) > 0 && board[y - 1][x] != Empty)
            return true;
        if ((x + 1) < board.getSize(static_cast<uint32_t >(y)) && board[y][x + 1] != Empty)
            return true;
        if ((y + 1) < board.getSize() && board[y + 1][x] != Empty)
            return true;
        if ((x - 1) >= 0 && (y - 1) >= 0 && board[y - 1][x - 1] != Empty)
            return true;
        if ((x + 1) < board.getSize(static_cast<uint32_t >(y)) && (y - 1) >= 0 && board[y - 1][x + 1] != Empty)
            return true;
        if ((x + 1) < board.getSize(static_cast<uint32_t >(y)) && (y + 1) < board.getSize(static_cast<uint32_t >(y)) &&
            board[y + 1][x + 1] != Empty)
            return true;
        if ((x - 1) >= 0 && (y + 1) < board.getSize(static_cast<uint32_t >(y)) && board[y + 1][x - 1] != Empty)
            return true;
    }
    return false;
}
