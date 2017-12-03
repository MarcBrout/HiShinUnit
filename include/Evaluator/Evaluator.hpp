//
// Created by Marc on 02/12/2017.
//

#ifndef GOMOKU_EVALUATOR_HPP
#define GOMOKU_EVALUATOR_HPP

#include <map>
#include <memory>
#include <functional>
#include <vector>
#include "Board.hpp"
#include "Position.hpp"

class Evaluator {
public:
    Evaluator() = default;

    std::vector<Position> evaluateBoard(Board const &board, uint32_t minimumLvl, CellState player, uint8_t limit = 10);
private:
    uint32_t evaluatePoint(Board const &board, Position const &play, CellState player) const;
};

#endif //GOMOKU_EVALUATOR_HPP
