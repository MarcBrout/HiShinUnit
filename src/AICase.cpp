//
// Created by Pierre Bougon on 28/11/2017.
//

#include "AICase.hpp"


ai::AICase::AICase()
        : board(), weight(0.0)
{
}

ai::AICase::AICase(std::unique_ptr<Board> newBoard, size_t round)
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
