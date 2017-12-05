//
// Created by Marc on 02/12/2017.
//

#include "Logic/Position.hpp"

Position &Position::operator=(Position const &pos)
{
    if (&pos != this)
    {
        x = pos.x;
        y = pos.y;
    }
    return *this;
}

Position::Position(Position const &pos)
{
    x = pos.x;
    y = pos.y;
}

std::string Position::toString() const {
    return std::string(std::to_string(x) + "," + std::to_string(y));
}

Position Position::operator+(Move const &move) const
{
    Position pos(*this);

    pos.x += move.x;
    pos.y += move.y;
    return pos;
}

bool Position::operator==(Position const &pos) const
{
    return pos.x == x && pos.y == y;
}