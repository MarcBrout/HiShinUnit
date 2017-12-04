//
// Created by Zenox on 11/28/2017.
//

#ifndef GOMOKU_POSITION_HPP
#define GOMOKU_POSITION_HPP

#include <cstdint>
#include <string>
#include "Shin/Evaluator/Move.h"

struct Position
{
    uint32_t x;
    uint32_t y;

    // Constructors
    explicit Position(uint32_t x = 0, uint32_t y = 0) : x(x), y(y) {}
    Position(Position const& pos);
    Position(Position &&) = default;
    ~Position() = default;

    // Copy operator
    Position &operator=(Position const &pos);
    Position &operator=(Position &&) = default;

    // Special Interaction with the Move structure
    Position operator+(Move const &move) const;

    std::string toString() const;
    bool operator==(Position const &pos);
};

#endif //GOMOKU_POSITION_HPP
