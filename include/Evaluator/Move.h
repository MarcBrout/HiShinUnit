//
// Created by Marc on 02/12/2017.
//

#ifndef GOMOKU_MOVE_H
#define GOMOKU_MOVE_H

#include <cstdint>

struct Move {
    int8_t x;
    int8_t y;

    Move(int8_t x = 0, int8_t y = 0) : x(x), y(y) {}
};

#endif //GOMOKU_MOVE_H
