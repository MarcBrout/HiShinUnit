//
// Created by Zenox on 11/29/2017.
//

#ifndef GOMOKU_MONTECARLOCASE_HPP
#define GOMOKU_MONTECARLOCASE_HPP

#include "AICase.hpp"

namespace ai {
    class MonteCarloCase : public AICase {
    public:
        MonteCarloCase(Board const &board, uint32_t x, uint32_t y, size_t round);
        void process() override;

    private:
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
