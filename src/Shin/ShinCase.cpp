//
// Created by 53818 on 04/12/2017.
//

#include <iostream>
#include "Shin/ShinCase.hpp"

namespace ai {

    void ShinCase::process() {
        weight = evaluator.evaluatePoint(*board, pos, player);
    }

    Position const &ShinCase::operator*() const {
        return pos;
    }


    ShinCase::ShinCase(Board const &board, uint32_t x, uint32_t y, size_t round, CellState player) :
        AICase(std::make_unique<Board>(board), x, y, round, player)
    {
    }
}