//
// Created by Marc on 02/12/2017.
//

#include <cmath>
#include <functional>
#include "Shin/Evaluator/Line.hpp"

namespace ai {
    bool isPlayer(CellState in, CellState player) {
        return in == player;
    }

    bool isFree(CellState in, CellState player) {
        return in == player || in == CellState::Empty;
    }

    uint8_t Line::getLength(Board const &board) {
        Position lengthLeftPos(central);
        Position lengthRightPos(central);

        uint8_t lengthRight;
        uint8_t lengthLeft;

        countPlayerGoPieces(board, lengthLeftPos, moves, direction, player, lengthLeft, isFree);
        countPlayerGoPieces(board, lengthRightPos, oppositeMoves, direction, player, lengthRight, isFree);

        return (lengthLeft + lengthRight + 1);
    }

    bool areEndsFree(CellState leftCell, CellState rightCell) {
        return leftCell == CellState::Empty && rightCell == CellState::Empty;
    }

    bool isOneEndFree(CellState leftCell, CellState rightCell) {
        return leftCell == CellState::Empty || rightCell == CellState::Empty;
    }

    uint32_t Line::propagate(Board const &board) {
        CellState leftCell = countPlayerGoPieces(board, left, moves, direction, player, countLeft, isPlayer);
        CellState rightCell = countPlayerGoPieces(board, right, oppositeMoves, direction, player, countRight, isPlayer);

        uint8_t length = getLength(board);

        // The more the central position is close to the center of the board the more it's valuable
        value = relativePositionEvaluation(board, central);

        // Evaluating the point
        switch (countLeft + countRight) {
            case 1:
                if (areEndsFree(leftCell, rightCell))
                    value = Values::LOW_HIGH;
                else if (isOneEndFree(leftCell, rightCell))
                    value = Values::LOW;
                else
                    value = Values::LOW;
                break;
            case 2:
                if (areEndsFree(leftCell, rightCell)) {
                    if (length > 5)
                        value = Values::MEDIUM_HIGH;
                    else
                        value = Values::MEDIUM;
                } else if (isOneEndFree(leftCell, rightCell)) {
                    value = Values::LOW_HIGH;
                } else {
                    value = LOW;
                }
                break;
            case 3:
                if (areEndsFree(leftCell, rightCell)) {
                    if (length > 5)
                        value = Values::WIN;
                    else
                        value = Values::VERY_HIGH;
                } else if (isOneEndFree(leftCell, rightCell) && length > 4)
                    value = Values::HIGH;
                else
                    value = LOW_HIGH;
                break;
            default:
                if (countRight + countLeft >= 4)
                    value = Values::FINAL_WIN;
                break;
        }
        return (countLeft + countRight);
    }

    inline int32_t absolute(int32_t val) {
        return (val > 0 ? val : -val);
    }

    uint32_t Line::relativePositionEvaluation(Board const &board, Position const &pos) {
        int32_t size = board.getSize();
        int32_t posX = central.x;
        int32_t posY = central.y;

        return static_cast<uint32_t >(size - absolute(size / 2 - posX) + size - absolute(size / 2 - posY)) / 2;
    }

    Line::Line(Position const &central, Direction const &direction, CellState const &player)
            :
            moves(
                    {
                            {Direction::North,     Move(0, -1)},
                            {Direction::NorthEast, Move(1, -1)},
                            {Direction::East,      Move(1, 0)},
                            {Direction::SouthEast, Move(1, 1)},
                            {Direction::South,     Move(0, 1)},
                            {Direction::SouthWest, Move(-1, 1)},
                            {Direction::West,      Move(-1, 0)},
                            {Direction::NorthWest, Move(-1, -1)}
                    }),
            oppositeMoves(
                    {
                            {Direction::South,     Move(0, -1)},
                            {Direction::SouthWest, Move(1, -1)},
                            {Direction::West,      Move(1, 0)},
                            {Direction::NorthWest, Move(1, 1)},
                            {Direction::North,     Move(0, 1)},
                            {Direction::NorthEast, Move(-1, 1)},
                            {Direction::East,      Move(-1, 0)},
                            {Direction::SouthEast, Move(-1, -1)}
                    }),
            central(central),
            direction(direction),
            player(player),
            left(central),
            right(central),
            countLeft(0),
            countRight(0),
            length(0),
            value(Values::NONE) {
    }

    uint32_t Line::getValue() const {
        return value;
    }
}