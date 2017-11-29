//
// Created by Pierre Bougon on 28/11/2017.
//

#include "AICase.hpp"


ai::AICase::AICase()
        : board(), weight(0.0)
{
}

ai::AICase::AICase(const ai::AICase &other)
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
    return nullptr;
}

ai::AICase &ai::AICase::operator=(const ai::AICase &other)
{
    this->board = std::make_unique(other.board);
    this->weight = other.weight;
    this->round = other.round;
    return *this;
}

size_t ai::AICase::getRound() const
{
    return round;
}

void ai::AICase::setRound(size_t round)
{
    AICase::round = round;
}
