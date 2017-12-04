//
// Created by Pierre Bougon on 28/11/2017.
//

#include <iostream>
#include "Logic/AICase.hpp"

ai::AICase::AICase()
        : board(), weight(0.0)
{
}

ai::AICase::AICase(std::unique_ptr<Board> newBoard,
                   uint32_t x,
                   uint32_t y,
                   size_t startRound) :
    board(std::move(newBoard)),
    weight(0.0),
    round(startRound),
    pos(x, y)
{
   // std::cout << "CONSTRUCTION : " << pos.x << " & " << pos.y << std::endl;
}

ai::AICase::AICase(std::unique_ptr<Board> newBoard, size_t startRound) :
        board(std::move(newBoard)),
        weight(0.0),
        round(startRound)
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
