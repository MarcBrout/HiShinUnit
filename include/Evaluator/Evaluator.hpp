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
#include "Point.hpp"
#include "Position.hpp"

class Evaluator {
public:
    Evaluator() = default;

    std::vector<std::pair<Position, uint32_t>>
    evaluateBoard(Board const &board, CellState player, uint8_t limit = 10, uint32_t minimumLvl = Point::NONE);
    uint32_t evaluateBoard_max_if(const Board &board, Position &outPos, CellState player,
                              const std::function<bool(Board const &, uint32_t const &,
                                                       uint32_t const &)> &check);

    std::vector<std::pair<Position, uint32_t>> evaluateBoard_if(const Board &board, Position &outPos, CellState player,
                                                                const std::function<bool(const Board &, const uint32_t &,
                                                                                         const uint32_t &)> &check,
                                                                uint32_t limit = 5);

private:
    uint32_t evaluatePoint(Board const &board, Position const &play, CellState player) const;

};

#endif //GOMOKU_EVALUATOR_HPP
