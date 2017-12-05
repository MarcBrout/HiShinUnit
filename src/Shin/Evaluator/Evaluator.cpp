//
// Created by Marc on 02/12/2017.
//

#include <map>
#include <cmath>
#include <iostream>
#include "Shin/Evaluator/Line.hpp"
#include "Shin/Evaluator/Evaluator.hpp"

namespace ai {
    std::vector<std::pair<Position, uint32_t>>
    Evaluator::evaluateBoard(Board const &board, CellState player, uint8_t limit, uint32_t minimumValue) {
        std::vector<std::pair<Position, uint32_t>> filteredPosition;

        for (uint32_t y = 0; y < board.getSize(); ++y) {
            for (uint32_t x = 0; x < board.getSize(); ++x) {
                if (board[y][x] == CellState::Empty) {
                    Position pos(x, y);
                    uint32_t value = evaluatePoint(board, pos, player);

                    if (value >= minimumValue) {
                        filteredPosition.emplace_back(std::make_pair(pos, value));
                    }
                }
            }
        }

        std::sort(filteredPosition.begin(), filteredPosition.end(),
                  [](std::pair<Position, uint32_t> &a, std::pair<Position, uint32_t> &b) {
                      return a.second > b.second;
                  });

        filteredPosition.resize(limit);
        return filteredPosition;
    }

    std::vector<std::pair<Position, uint32_t>>
    Evaluator::evaluateBoard_if(const Board &board, Position &outPos, CellState player,
                                const std::function<bool(Board const &, uint32_t const &,
                                                         uint32_t const &)> &check,
                                uint32_t limit) {
        std::vector<std::pair<Position, uint32_t>> filteredPosition;

        for (uint32_t y = 0; y < board.getSize(); ++y) {
            for (uint32_t x = 0; x < board.getSize(); ++x) {
                if (check(board, x, y)) {
                    Position pos(x, y);
                    filteredPosition.emplace_back(std::make_pair(pos, evaluatePoint(board, pos, player)));
                }
            }
        }

        std::sort(filteredPosition.begin(), filteredPosition.end(),
                  [](std::pair<Position, uint32_t> &a, std::pair<Position, uint32_t> &b) {
                      return a.second > b.second;
                  });

        filteredPosition.resize(limit);
        return filteredPosition;
    }

    uint32_t
    Evaluator::evaluateBoard_max_if(const Board &board, Position &outPos, CellState player,
                                    const std::function<bool(Board const &, uint32_t const &,
                                                             uint32_t const &)> &check) {
        Position tmp;
        int32_t max = -1;

        for (uint32_t y = 0; y < board.getSize(); ++y) {
            for (uint32_t x = 0; x < board.getSize(); ++x) {
                tmp.x = x;
                tmp.y = y;
                if (check(board, x, y)) {
                    uint32_t value = evaluatePoint(board, tmp, player);
                    if (static_cast<int32_t>(value) > max) {
                        outPos = tmp;
                        max = value;
                    }
                }
            }
        }
        return static_cast<uint32_t >(max);
    }

    uint32_t Evaluator::evaluatePoint(Board const &board, Position const &play, CellState player) const {
        std::vector<Line> Lines;
        std::vector<uint32_t> values;
        uint32_t totalAround = 0;

        // Only doing half of the directions because we're checking full lines
        Lines.emplace_back(Line(play, Line::Direction::North, player));
        Lines.emplace_back(Line(play, Line::Direction::NorthEast, player));
        Lines.emplace_back(Line(play, Line::Direction::East, player));
        Lines.emplace_back(Line(play, Line::Direction::SouthEast, player));

        std::for_each(Lines.begin(), Lines.end(), [&board, &values, &totalAround](Line &point) {
            totalAround += point.propagate(board);
            values.push_back(point.getValue());
        });

        int veryHighCount = 0;

        for (uint32_t const& value : values) {
            if (value == Line::FINAL_WIN)
                return Line::FINAL_WIN;
            if (value == Line::WIN)
                return Line::WIN;
            if (value >= Line::MEDIUM_HIGH)
                ++veryHighCount;
        }

        if (veryHighCount > 1) {
            return (Line::WIN);
        }

        auto it = std::max_element(values.begin(), values.end());

        if (*it >= Line::MEDIUM_HIGH && totalAround >= 4)
            return Line::HIGH;
        return *it;
    }
}