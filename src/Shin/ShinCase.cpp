//
// Created by 53818 on 04/12/2017.
//

#include "Shin/ShinCase.hpp"

namespace ai {

    void ShinCase::process() {

    }

    ShinCase &ShinCase::operator=(uint32_t value) {
        this->value = value;
        return *this;
    }

    Position const &ShinCase::operator*() const {
        return pos;
    }

    ShinCase::ShinCase(Board const &board, uint32_t x, uint32_t y) :
        board(board),
        pos(x, y)
    {

    }
}