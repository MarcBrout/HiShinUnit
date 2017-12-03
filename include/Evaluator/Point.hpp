//
// Created by Marc on 02/12/2017.
//

#ifndef GOMOKU_LINE_HPP
#define GOMOKU_LINE_HPP


#include <map>
#include "Cell.hpp"
#include "Board.hpp"
#include "Position.hpp"

class Point {
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
        WIN = 100
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
    Point(Position const &central, Direction const &direction, CellState const &player);

    // Public Methods
public:
    void propagate(Board const& board);
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
    CellState move(Board const &board,
                   Position &pos,
                   Move const &move,
                   CellState player,
                   const std::function<bool(CellState, CellState)> &cmp);
    CellState countPlayerGoPieces(const Board &board,
                                  Position &pos,
                                  const std::map<Direction, Move> &moves,
                                  Direction direction,
                                  CellState player,
                                  uint8_t &outCount,
                                  const std::function<bool(CellState, CellState)> &cmp);
    uint8_t getLength(Board const &board);

};


#endif //GOMOKU_LINE_HPP
