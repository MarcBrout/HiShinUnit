//
// Created by Zenox on 11/29/2017.
//

#ifndef GOMOKU_MONTECARLOCASE_HPP
#define GOMOKU_MONTECARLOCASE_HPP

#include "AICase.hpp"

namespace ai {
    class MonteCarloCase : AICase {
    public:
        MonteCarloCase(Board &board, uint32_t x, uint32_t y);
        void process() override;

    private:
        uint32_t x;
        uint32_t y;
        Checker checker;

    private:
        bool canIWinRow(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y);
        bool canIWinCol(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y);
        bool canIWinDia(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y);
        bool canIWin(Board &myBoard, Position &out, CellState player);
        bool enemyCanWin(Board &myBoard, Position &out, CellState player );
        CellState recurs(Board &board, uint32_t x, uint32_t y, CellState state);
    };
}

#endif //GOMOKU_MONTECARLOCASE_HPP
