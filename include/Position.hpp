//
// Created by Zenox on 11/28/2017.
//

#ifndef GOMOKU_POSITION_HPP
#define GOMOKU_POSITION_HPP

#include <cstdint>
#include <string>

struct Position
{
    uint32_t x;
    uint32_t y;

    std::string toString() {
        return std::string(x + "," + y);
    }
};

#endif //GOMOKU_POSITION_HPP
