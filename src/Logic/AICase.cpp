//
// Created by Pierre Bougon on 28/11/2017.
//

#include <iostream>
#include "Logic/AICase.hpp"

ai::AICase::AICase(std::unique_ptr<Board> newBoard,
                   uint32_t x,
                   uint32_t y,
                   size_t startRound,
                   CellState player) :
    board(std::move(newBoard)),
    weight(0.0),
    round(startRound),
    pos(x, y),
    player(player)
{
}

void ai::AICase::resetWeight()
{
    weight = 0.0;
}

void ai::AICase::setBoard(std::unique_ptr<Board> newBoard)
{
    board = std::move(newBoard);
}

double ai::AICase::getWeight()
{
    return weight;
}

size_t ai::AICase::getRound() const
{
    return round;
}

void ai::AICase::setRound(size_t round)
{
    this->round = round;
}

const Position &ai::AICase::getPos() const {
    return pos;
}

CellState ai::AICase::getPlayer() const {
    return player;
}
