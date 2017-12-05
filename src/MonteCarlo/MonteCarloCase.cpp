//
// Created by Zenox on 11/29/2017.
//

#include <iostream>
#include "Shin/Evaluator/Evaluator.hpp"
#include "MonteCarlo/CanIProcess.hpp"
#include "MonteCarlo/MonteCarloCase.hpp"

namespace ai {
    bool MonteCarloCase::canIWinRow(Board &myBoard, Position &out, CellState player,
                                    uint32_t x, uint32_t y, uint32_t limit) {
        if (checker.checkCanWinRow(myBoard.getBoard(), x, y, player) >= limit) {
            for (int32_t pos = 1; pos < 5; ++pos)
            {
                if (pos == 0)
                    continue;
                if (checker.checkInRow(myBoard.getBoard(), x, y, pos))
                {
                    out.x = x + pos;
                    out.y = y;
                    return true;
                }
            }
            if (checker.checkInRow(myBoard.getBoard(), x, y, -1))
            {
                out.x = x - 1;
                out.y = y;
                return true;
            }
        }
        return false;
    }

    bool MonteCarloCase::canIWinCol(Board &myBoard, Position &out, CellState player,
                                    uint32_t x, uint32_t y, uint32_t limit) {
        if (checker.checkCanWinCol(myBoard.getBoard(), x, y, player) >= limit) {
            for (int32_t pos = 1; pos < 5; ++pos)
            {
                if (pos == 0)
                    continue;
                if (checker.checkInCol(myBoard.getBoard(), x, y, pos))
                {
                    out.x = x;
                    out.y = y + pos;
                    return true;
                }
            }
            if (checker.checkInCol(myBoard.getBoard(), x, y, -1))
            {
                out.x = x;
                out.y = y - 1;
                return true;
            }
        }
        return false;
    }

    bool MonteCarloCase::canIWinDia(Board &myBoard, Position &out, CellState player,
                                    uint32_t x, uint32_t y, uint32_t limit) {
        if (checker.checkCanWinDiaLeft(myBoard.getBoard(), x, y, player) >= limit) {
            for (int32_t pos = 1; pos < 5; ++pos)
            {
                if (pos == 0)
                    continue;
                if (checker.checkInDiaLeft(myBoard.getBoard(), x, y, pos))
                {
                    out.x = x - pos;
                    out.y = y + pos;
                    return true;
                }
            }
            if (checker.checkInDiaLeft(myBoard.getBoard(), x, y, -1))
            {
                out.x = x + 1;
                out.y = y - 1;
                return true;
            }
        } else if (checker.checkCanWinDiaRight(myBoard.getBoard(), x, y, player) >= limit) {
            for (int32_t pos = 1; pos < 5; ++pos)
            {
                if (pos == 0)
                    continue;
                if (checker.checkInDiaRight(myBoard.getBoard(), x, y, pos))
                {
                    out.x = x + pos;
                    out.y = y + pos;
                    return true;
                }
            }
            if (checker.checkInDiaRight(myBoard.getBoard(), x, y, -1))
            {
                out.x = x - 1;
                out.y = y - 1;
                return true;
            }
        }
        return false;
    }

    bool MonteCarloCase::canThisPlayerWin(Board &myBoard, Position &out, CellState player, uint32_t limit) {
        for (uint32_t y = 0; y < myBoard.getSize(); ++y) {
            for (uint32_t x = 0; x < myBoard.getSize(y); ++x) {
                if (myBoard[y][x] == player) {
                    if (canIWinRow(myBoard, out, player, x, y, limit) ||
                        canIWinCol(myBoard, out, player, x, y, limit) ||
                        canIWinDia(myBoard, out, player, x, y, limit)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    CellState MonteCarloCase::recurs(Board &myBoard, uint32_t x, uint32_t y, CellState state) {
        CellState comp;

        // Placing last play on board and check if we have a winner
        myBoard.setCellState(x, y, state);
        comp = myBoard.getChecker().hasAWinner(myBoard.getBoard());
        if (comp == Player1 || comp == Player2)
            return comp;

        if (myBoard.isFill())
            return Empty;

        // Swapping player Role;
        state = state == Player1 ? Player2 : Player1;

        Position out;
        // Determine if we can end the game with this move
        if (canThisPlayerWin(myBoard, out, state, 5) ||
            canThisPlayerWin(myBoard, out, (state == Player2) ? Player1 : Player2, 4)) {
            return recurs(myBoard, out.x, out.y, state);
        }

        // Select a random cell to perform the recursive
       do {
            out.x = static_cast<uint32_t>(std::rand() % 19);
            out.y = static_cast<uint32_t>(std::rand() % 19);
        } while (myBoard[out.y][out.x] != CellState::Empty);
        return recurs(myBoard, out.x, out.y, state);
    }


    void MonteCarloCase::process() {
        uint32_t result = 0;
        Position checkPos;

        // Checking if I can win
        if (canThisPlayerWin(*board, checkPos, Player1, 4)) {
            if (checkPos == pos)
                weight = 95;
            if (canThisPlayerWin(*board, checkPos, Player1, 5)) {
                if (checkPos == pos)
                    weight = 100;
                return;
            }
        }

        // Checking if I can lose
        if (canThisPlayerWin(*board, checkPos, Player2, 4))
        {
            if (checkPos == pos)
                weight = 95;
            if (canThisPlayerWin(*board, checkPos, Player2, 5)) {
                if (checkPos == pos)
                    weight = 99;
            }
            return;
        }

        // Launch x recursive here, and increment the result for each win of player1
        constexpr uint32_t launches = 100;
        for (uint32_t idx = 0; idx < launches; ++idx) {
            Board copy(*board);
            if (recurs(copy, pos.x, pos.y, Player1) == Player1)
                result++;
        }
        weight = result / launches * 100.0;
    }

    MonteCarloCase::MonteCarloCase(Board const &board_c,
                                   uint32_t x, uint32_t y, size_t round)
            : AICase(std::make_unique<Board>(board_c), x, y, round),
              checker()
    {
    }
}