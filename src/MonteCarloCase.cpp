//
// Created by Zenox on 11/29/2017.
//

#include <iostream>
#include "MonteCarloCase.hpp"

namespace ai {
    bool MonteCarloCase::canIWinRow(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y) {
        if (checker.checkWinRow(myBoard.getBoard(), x, y, player) == 4) {
            if (checker.checkInRowBefore(myBoard.getBoard(), x, y)) {
                out.x = x - 1;
                out.y = y;
                return true;
            } else if (checker.checkInRowAfter(myBoard.getBoard(), x, y)) {
                out.x = x + 4;
                out.y = y;
                return true;
            }
        }
        return false;
    }

    bool MonteCarloCase::canIWinCol(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y) {
        if (checker.checkWinCol(myBoard.getBoard(), x, y, player) == 4) {
            if (checker.checkInColBefore(myBoard.getBoard(), x, y)) {
                out.x = x;
                out.y = y - 1;
                return true;
            } else if (checker.checkInColAfter(myBoard.getBoard(), x, y)) {
                out.x = x;
                out.y = y + 4;
                return true;
            }
        }
        return false;
    }

    bool MonteCarloCase::canIWinDia(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y) {
        if (checker.checkWinDiaLeft(myBoard.getBoard(), x, y, player) == 4) {
            if (checker.checkInDiaLeftBefore(myBoard.getBoard(), x, y)) {
                out.x = x + 1;
                out.y = y - 1;
                return true;
            } else if (checker.checkInDiaLeftAfter(myBoard.getBoard(), x, y)) {
                out.x = x - 4;
                out.y = y + 4;
                return true;
            }
        } else if (checker.checkWinDiaRight(myBoard.getBoard(), x, y, player) == 4) {
            if (checker.checkInDiaRightBefore(myBoard.getBoard(), x, y)) {
                out.x = x - 1;
                out.y = y - 1;
                return true;
            } else if (checker.checkInDiaRightAfter(myBoard.getBoard(), x, y)) {
                out.x = x + 4;
                out.y = y + 4;
                return true;
            }
        }
        return false;
    }

    bool MonteCarloCase::enemyCanWin(Board &myBoard, Position &out, CellState player) {
        //TODO Check if the enemy can win next round
        return false;
    }

    bool MonteCarloCase::canIWin(Board &myBoard, Position &out, CellState player) {
        for (uint32_t y = 0; y < myBoard.getBoard().size(); ++y) {
            for (uint32_t x = 0; x < myBoard[y].size(); ++x) {
                if (myBoard[y][x] == player) {
                    if (canIWinRow(myBoard, out, player, x, y) ||
                        canIWinCol(myBoard, out, player, x, y) ||
                        canIWinDia(myBoard, out, player, x, y)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    CellState MonteCarloCase::recurs(Board &myBoard, uint32_t x, uint32_t y, CellState state) {
        CellState comp;

        //std::cout << x << " && " << y << " ================" << std::endl;
        //Set the piece at the position giving in param.
        myBoard.setCellState(x, y, state);

        /* for (auto const &line : myBoard.getBoard()) {
            for (CellState const &cell : line) {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }*/

        //std::cout << " LET'S BEGIN" << std::endl;
        //Check
        comp = myBoard.getChecker().hasAWinner(myBoard.getBoard());
        if (comp == Player1)
            return Player1;
        else if (comp == Player2)
            return Player2;

        //std::cout << " AFTER CHECK PLAYER WIN" << std::endl;
        if (myBoard.isFill())
            return Empty;
        Position out;
        //Change player Role;
        if (state == Player1)
            state = Player2;
        else
            state = Player1;

        //std::cout << " SWITCH PLAYER ROLE" << std::endl;
        // Determine if we can end the game with one move
        if (canIWin(myBoard, out, state)) {
            if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
                return comp;
            return Empty;
        }
        //std::cout << " CAN I WIN ?" << std::endl;
        if (enemyCanWin(myBoard, out, (state == Player2) ? Player1 : Player2)) {
            if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
                return comp;
            return Empty;
        }
        //std::cout << " ENEMY CAN WIN ?" << std::endl;

        // Select a random cell to perform the recursive
        do {
            out.x = static_cast<uint32_t>(std::rand() % 19);
            out.y = static_cast<uint32_t>(std::rand() % 19);
        } while (myBoard[out.y][out.x] != CellState::Empty);
        //std::cout << " RANDOMINATOR" << std::endl;
        if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
            return comp;
      //  std::cout << " BITCH" << std::endl;
        return Empty;
    }


    void MonteCarloCase::process() {
        uint32_t result = 0;

        //Launch x recursive here 1000, and growth the var result for each win of player 1
        for (uint32_t idx = 0; idx < 5; ++idx) {
            Board copy(*board);
           /* for (auto const &line : copy.getBoard()) {
                for (CellState const &cell : line) {
                    std::cout << cell << " ";
                }
                std::cout << "\n";
            }*/
            //std::cout << "Idx : " << idx << std::endl;
            if (recurs(copy, pos.x, pos.y, Player1) == Player1)
                result++;
        }
        weight = result;
    }

    MonteCarloCase::MonteCarloCase(Board const &board_c,
                                   uint32_t x, uint32_t y, size_t round)
            : AICase(std::make_unique<Board>(board_c), x, y, round),
              checker()
    {
    }
}