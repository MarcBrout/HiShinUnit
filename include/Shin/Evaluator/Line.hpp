//
// Created by Marc on 02/12/2017.
//

#ifndef GOMOKU_LINE_HPP
#define GOMOKU_LINE_HPP

#include <functional>
#include <map>
#include "Logic/Cell.hpp"
#include "Logic/Board.hpp"
#include "Logic/Position.hpp"
#include "Shin/Evaluator/Move.h"

namespace ai {
    class Line {
        // Public types
    public:
        enum Values {
            NONE = 0,
            VERY_LOW = 10,
            LOW = 20,
            LOW_HIGH = 30,
            MEDIUM_LOW = 40,
            MEDIUM = 50,
            MEDIUM_HIGH = 60,
            HIGH_LOW = 70,
            HIGH = 80,
            VERY_HIGH = 90,
            WIN = 100,
            FINAL_WIN = 105
        };

        enum Direction {
            North = 0,
            NorthEast,
            East,
            SouthEast,
            South,
            SouthWest,
            West,
            NorthWest,
            DirectionEnd
        };

        // Public Constructors
    public:
        Line(Position const &central, Direction const &direction, CellState const &player);

        // Public Methods
    public:
        /**
         * Method used to trace the line
         * @param board on which the line must be propagated
         * @return the count of the player Go pieces on the line
         */
        uint32_t propagate(Board const &board);

        // Get the value of the line
        uint32_t getValue() const;

    private:
        const std::map<Direction, Move> moves;
        const std::map<Direction, Move> oppositeMoves;
        Position central;
        Direction direction;
        CellState player;
        Position left;
        Position right;
        uint8_t countLeft;
        uint8_t countRight;

        uint8_t length;
        uint32_t value;

        // Methods
    private:
        uint32_t relativePositionEvaluation(Board const &board, Position const &pos);

        template <typename Function>
        CellState move(Board const &board,
                       Position &pos,
                       Move const &move,
                       CellState player,
                       Function cmp) {
            Position result(pos + move);

            if (result.x >= board.getSize() ||
                result.y >= board.getSize()) {
                return OutOfBound;
            }

            if (!cmp(board[result.y][result.x], player)) {
                return board[result.y][result.x];
            }
            pos = result;
            return player;
        }

        template<typename Function>
        CellState countPlayerGoPieces(const Board &board,
                                      Position &pos,
                                      const std::map<Direction, Move> &actions,
                                      Direction direction,
                                      CellState player,
                                      uint8_t &outCount,
                                      Function &cmp) {
            CellState lastCell;

            // Moving in the direction until I'm blocked by the cmp function
            do {
                lastCell = move(board, pos, actions.at(direction), player, cmp);
                ++outCount;
            } while (lastCell == player || outCount > 6);

            // Removing one move because we move one case too far
            --outCount;

            return lastCell;
        }

        uint8_t getLength(Board const &board);

        // Deleted constructors and operators
    public:
        Line() = delete;
    };
}

#endif //GOMOKU_LINE_HPP
