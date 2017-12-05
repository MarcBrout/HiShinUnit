//
// Created by 53818 on 04/12/2017.
//

#include <Shin/ShinHalbard.hpp>
#include <iostream>
#include "Shin/ShinCase.hpp"
#include "Shin/ShinAI.hpp"

namespace ai {

    void ShinAI::initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases, size_t round) {
        for (uint32_t y = 0; y < board.getSize(); ++y) {
            for (uint32_t x = 0; x < board.getSize(); ++x) {
                if (board[y][x] == CellState::Empty) {
                    threadPool.addCase(std::make_unique<ai::ShinCase>(board, x, y, round, CellState::Player1));
                    threadPool.addCase(std::make_unique<ai::ShinCase>(board, x, y, round, CellState::Player2));
                }
            }
        }
    }

    void ShinAI::resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) {
        myPlays.clear();
        enemyPlays.clear();

        // Splitting the processed cases in their respective container
        while (!casesDone.empty()) {
            if ((*casesDone.front()).getPlayer() == CellState::Player1) {
                const Position& pos = (*casesDone.front()).getPos();
                myPlays.addCase(casesDone.front());
            } else {
                Position const &pos = (*casesDone.front()).getPos();
                enemyPlays.addCase(casesDone.front());
            }
            casesDone.pop_front();
        }

        // Can I win ?
        if (myPlays.getCount(Line::FINAL_WIN) > 0) {
            simplePlay(posOut, Line::FINAL_WIN, myPlays);
            return ;
        }

        // Can I Lose ?
        if (enemyPlays.getCount(Line::FINAL_WIN) > 0) {
            simplePlay(posOut, Line::FINAL_WIN, enemyPlays);
            return ;
        }

        uint32_t myWins = myPlays.getCount(Line::WIN);
        uint32_t enemyWins = enemyPlays.getCount(Line::WIN);

        if (myWins > enemyWins) {
            fusionPlays(posOut, Line::WIN, CellState::Player1);
        } else if (enemyWins > myWins) {
            fusionPlays(posOut, Line::WIN, CellState::Player2);
        } else {
            fusionPlays(posOut, Line::HIGH, Empty);
        }
    }

    bool findCommonValuePosition(std::vector<Position> const &myFusion, std::vector<Position> const &enemyFusion, Position &outPos) {
        for (Position const &myPos : myFusion) {
            for (Position const &enemyPos : enemyFusion) {
                if (myPos == enemyPos) {
                    outPos = myPos;
                    return true;
                }
            }
        }
        return false;
    }

    void ShinAI::fusionPlays(Position &outPos, Line::Values value, CellState priority) {
        Line::Values myBestPlay;
        Line::Values enemyBestPlay;
        std::vector<Position> myFusion = myPlays.getMaxPositions(value, myBestPlay);
        std::vector<Position> enemyFusion = enemyPlays.getMaxPositions(value, enemyBestPlay);

        if (priority != CellState::Empty) {
            if (!myFusion.empty() && !enemyFusion.empty() && findCommonValuePosition(myFusion, enemyFusion, outPos)) {
                return;
            }
            if (priority == CellState::Player1) {
                outPos = myFusion.front();
            } else {
                outPos = enemyFusion.front();
            }
        } else {
            if (myBestPlay > enemyBestPlay) {
                if (!myFusion.empty() && !enemyFusion.empty() && findCommonValuePosition(myFusion, enemyFusion, outPos)) {
                    return;
                }
                outPos = myFusion.front();
            } else if (enemyBestPlay > myBestPlay) {
                if (!myFusion.empty() && !enemyFusion.empty() && findCommonValuePosition(enemyFusion, myFusion, outPos)) {
                    return;
                }
                outPos = enemyFusion.front();
            } else {
                if (enemyFusion.size() > myFusion.size()) {
                    outPos = enemyFusion.front();
                } else {
                    outPos = myFusion.front();
                }
            }
        }
    }

    void ShinAI::simplePlay(Position &outPos, Line::Values value, ShinHalbard &halbard) {
        Line::Values best;
        std::vector<Position> plays = halbard.getMaxPositions(value, best);
        outPos = plays.front();
    }

    ShinAI::ShinAI(unsigned int threadCount, unsigned int timeLimit) : AAI(threadCount, timeLimit) {

    }
}