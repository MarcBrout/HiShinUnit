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

        //myPlays.print("MY PLAYS");
        //enemyPlays.print("ENEMY PLAYS");

        if (myPlays.getCount(Line::FINAL_WIN) > 0) {
            std::cout << "DEBUG MY FINAL MOVE, WIN" << std::endl;
            simplePlay(posOut, Line::FINAL_WIN, myPlays);
            return ;
        }

        if (enemyPlays.getCount(Line::FINAL_WIN) > 0) {
            std::cout << "DEBUG ENEMY FINAL MOVE, BLOCK" << std::endl;
            simplePlay(posOut, Line::FINAL_WIN, enemyPlays);
            return ;
        }

        uint32_t myWins = myPlays.getCount(Line::WIN);
        uint32_t enemyWins = enemyPlays.getCount(Line::WIN);
        std::cout << "DEBUG COUNT MY WINS :" << myWins << std::endl;
        std::cout << "DEBUG COUNT ENEMY WINS :" << enemyWins << std::endl;

        if (myWins > enemyWins) {
            std::cout << "DEBUG I HAVE MORE WINS" << std::endl;
            fusionPlays(posOut, Line::WIN, CellState::Player1);
        } else if (enemyWins > myWins) {
            std::cout << "DEBUG HE HAS MORE WINS" << std::endl;
            fusionPlays(posOut, Line::WIN, CellState::Player2);
        } else {
            std::cout << "DEBUG EVEN WINS OR NONE" << std::endl;
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
            std::cout << "DEBUG PRIORITY: ";
            if (!myFusion.empty() && !enemyFusion.empty() && findCommonValuePosition(myFusion, enemyFusion, outPos)) {
                std::cout << std::endl;
                return;
            }
            if (priority == CellState::Player1) {
                std::cout << "ME";
                outPos = myFusion.front();
            } else {
                std::cout << "ENEMY";
                outPos = enemyFusion.front();
            }
        } else {
            std::cout << "DEBUG NO PRIORITY: ";
            if (myBestPlay > enemyBestPlay) {
                std::cout << "I HAVE BETTER PLAYS";
                if (!myFusion.empty() && !enemyFusion.empty() && findCommonValuePosition(myFusion, enemyFusion, outPos)) {
                    std::cout << std::endl;
                    return;
                }
                outPos = myFusion.front();
            } else if (enemyBestPlay > myBestPlay) {
                std::cout << "HE HAS BETTER PLAYS";
                if (!myFusion.empty() && !enemyFusion.empty() && findCommonValuePosition(enemyFusion, myFusion, outPos)) {
                    std::cout << std::endl;
                    return;
                }
                outPos = enemyFusion.front();
            } else {
                std::cout << std::endl << "DEBUG NO ONE HAS BETTER PLAYS: ";
                if (enemyFusion.size() > myFusion.size()) {
                    std::cout << "HE HAS MORE PLAYS";
                    outPos = enemyFusion.front();
                } else {
                    std::cout << "I HAVE MORE PLAYS";
                    outPos = myFusion.front();
                }
            }
        }
        std::cout << std::endl;
    }

    void ShinAI::simplePlay(Position &outPos, Line::Values value, ShinHalbard &halbard) {
        Line::Values best;
        std::vector<Position> plays = halbard.getMaxPositions(value, best);
        outPos = plays.front();
    }

    ShinAI::ShinAI(unsigned int threadCount, unsigned int timeLimit) : AAI(threadCount, timeLimit) {

    }
}