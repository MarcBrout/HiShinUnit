//
// Created by Zenox on 11/28/2017.
//

#ifndef GOMOKU_POSITION_HPP
#define GOMOKU_POSITION_HPP

#include <cstdint>
#include <string>

struct Position
{
    uint32_t x = 0;
    uint32_t y = 0;

    std::string toString() {
        return std::string(std::to_string(x) + "," + std::to_string(y));
    }
};

#endif //GOMOKU_POSITION_HPP
