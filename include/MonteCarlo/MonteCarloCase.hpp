//
// Created by Zenox on 11/29/2017.
//

#ifndef GOMOKU_MONTECARLOCASE_HPP
#define GOMOKU_MONTECARLOCASE_HPP

#include "Logic/AICase.hpp"

namespace ai {
    class MonteCarloCase : public AICase {
    public:
        MonteCarloCase(Board const &board, uint32_t x, uint32_t y, size_t round);
        void process() override;

    private:
        Checker checker;

    private:
        bool canIWinRow(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y, uint32_t limit);
        bool canIWinCol(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y, uint32_t limit);
        bool canIWinDia(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y, uint32_t limit);
        bool canThisPlayerWin(Board &myBoard, Position &out, CellState player, uint32_t limit);
        CellState recurs(Board &board, uint32_t x, uint32_t y, CellState state);
    };
}

#endif //GOMOKU_MONTECARLOCASE_HPP
