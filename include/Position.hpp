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

    Position(uint32_t X, uint32_t Y) : x(X), y(Y) {}

    Position() = default;

    Position &operator=(Position &pos)
    {
        if (&pos != this)
        {
            x = pos.x;
            y = pos.y;
        }
        return *this;
    }

    std::string toString() {
        return std::string(std::to_string(x) + "," + std::to_string(y));
    }
};

#endif //GOMOKU_POSITION_HPP
