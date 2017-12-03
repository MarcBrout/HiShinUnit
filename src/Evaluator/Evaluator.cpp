//
// Created by Marc on 02/12/2017.
//

#include <cmath>
#include "Evaluator/Point.hpp"
#include "Evaluator/Evaluator.hpp"

std::vector<Position> Evaluator::evaluateBoard(Board const &board, uint32_t minimumValue, CellState player, uint8_t limit)
{
    std::vector<Position> filteredPosition;

    for (uint32_t y = 0; y < board.getSize(); ++y) {
        for (uint32_t x = 0; x < board.getSize(); ++x) {
            Position pos(x, y);
            uint32_t value = evaluatePoint(board, pos, player);

            if (value >= minimumValue) {
                filteredPosition.push_back(pos);
            }
        }
    }

    std::sort(filteredPosition.begin(), filteredPosition.end(), [](int a, int b) {
        return a > b;
    });

    filteredPosition.resize(limit);
    return filteredPosition;
}

uint32_t Evaluator::evaluatePoint(Board const &board, Position const &play, CellState player) const
{
    std::vector<Point> points;
    std::vector<uint32_t> values;

    // Only doing half of the directions because we're checking full lines
    points.emplace_back(Point(play, Point::Direction::North, player));
    points.emplace_back(Point(play, Point::Direction::NorthEast, player));
    points.emplace_back(Point(play, Point::Direction::East, player));
    points.emplace_back(Point(play, Point::Direction::West, player));

    std::for_each(points.begin(), points.end(), [](Point &point) {
        point.propagate(board);
        values.push_back(point.getValue());
    });

    int winCount = std::count(values.cbegin(), values.cend(), Point::WIN);
    int veryHighCount = std::count(values.cbegin(), values.cend(), Point::VERY_HIGH);

    if (winCount > 0 || veryHighCount > 1) {
        return (Point::WIN);
    }

    return *std::max(values.cbegin(), values.cend());
}
