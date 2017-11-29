//
// Created by Zenox on 11/29/2017.
//

#include "MonteCarloIA.hpp"

MonteCarloIA::MonteCarloIA(Board board1) : board(board1), checker()
{
}

bool MonteCarloIA::canIWinRow(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y) {
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

bool MonteCarloIA::canIWinCol(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y) {
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

bool MonteCarloIA::canIWinDia(Board &myBoard, Position &out, CellState player, uint32_t x, uint32_t y) {
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
    }
    else if (checker.checkWinDiaRight(myBoard.getBoard(), x, y, player) == 4) {
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



bool MonteCarloIA::enemyCanWin(Board &myBoard, Position &out, CellState player)
{
    //TODO Check if the enemy can win next round
    return false;
}

bool MonteCarloIA::canIWin(Board &myBoard, Position &out, CellState player)
{
    for (uint32_t y = 0; y < myBoard.getBoard().size(); ++y)
    {
        for (uint32_t x = 0; x < myBoard[y].size(); ++x)
        {
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

void MonteCarloIA::getIaPlay(Position &outPos) {
    Position curMax;
    // Count is the max probality value of the cell
    uint32_t count = 0;

    // Tmp will receive the return of monteCarlo algo and will be compared with count
    uint32_t tmp = 0;

    // lookinf for an Empty cell which i'll launch the monteCarlo recursive
    for (uint32_t y = 0; y < board.getBoard().size(); ++y)
    {
        for (uint32_t x = 0; x < board.getBoard()[y].size(); ++x)
        {
            if (board[y][x] == Empty) {
                if ((tmp = monteCarlo(x, y)) > count) {
                    // A new max prob has been happened, so set the new pos and the new count
                    count = tmp;
                    curMax.x = x;
                    curMax.y = y;
                }
            }
        }
    }
    outPos = curMax;
}

uint32_t MonteCarloIA::monteCarlo(uint32_t x, uint32_t y)
{
    uint32_t result = 0;
    auto tmpBoard = board;

    //Launch x recursive here 1000, and growth the var result for each win of player 1
    for (uint32_t idx = 0; idx < 1000; ++idx)
    {
        if (recurs(tmpBoard, x, y, Player1) == Player1)
            result++;
    }
    return result;
}

CellState MonteCarloIA::recurs(Board &myBoard, uint32_t x, uint32_t y, CellState state) {
    CellState comp;

    //Set the piece at the position giving in param.
    myBoard.setCellState(x, y, state);

    //Check
    comp = myBoard.getChecker().hasAWinner(myBoard.getBoard());
    if (comp == Player1)
        return Player1;
    else if (comp == Player2)
        return Player2;

    if (myBoard.isFill())
        return Empty;
    Position out;
    //Change player Role;
    if (state == Player1)
        state = Player2;
    else
        state = Player1;

    // Determine if we can end the game with one move
    if (canIWin(myBoard, out, state))
    {
        if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
            return comp;
    }
    if (enemyCanWin(myBoard, out, (state == Player2) ? Player1 : Player2))
    {
        if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
            return comp;
    }
    // Select a random cell to perform the recursive
    do {
        out.x = static_cast<uint32_t>(std::rand() % 19);
        out.y = static_cast<uint32_t>(std::rand() % 19);
    } while (myBoard[out.y][out.x] != CellState::Empty);
    if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
        return comp;
    return Empty;
}
