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

    Position &operator=(Position const &pos)
    {
        if (&pos != this)
        {
            x = pos.x;
            y = pos.y;
        }
        return *this;
    }

    bool operator==(Position const &pos)
    {
        return pos.x == x && pos.y == y;
    }

    Position(Position const& pos) {
        x = pos.x;
        y = pos.y;
    }

    std::string toString() const {
        return std::string(std::to_string(x) + "," + std::to_string(y));
    }
};

#endif //GOMOKU_POSITION_HPP
