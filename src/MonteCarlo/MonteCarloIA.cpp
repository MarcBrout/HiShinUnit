//
// Created by Zenox on 11/29/2017.
//

#include <iostream>
#include "Shin/Evaluator/Line.hpp"
#include "Shin/Evaluator/Evaluator.hpp"
#include "MonteCarlo/MonteCarloIA.hpp"
#include "MonteCarlo/MonteCarloCase.hpp"

static const unsigned int max_threads = std::thread::hardware_concurrency();

namespace ai {
    MonteCarloIA::MonteCarloIA() : AAI() {
    }

    void MonteCarloIA::initializeCases(Board const &board,
                                       std::deque<std::unique_ptr<ai::AICase>> &outCases,
                                       size_t round) {
        if (board.isEmpty()) {
            outCases.push_back(
                    std::make_unique<ai::MonteCarloCase>(board, board.getSize(0) / 2,
                                                         board.getSize() / 2,
                                                         round));
            return;
        }

        // Evaluating best cases scenarios
        ai::Evaluator evaluator;
        std::vector<std::pair<Position, uint32_t>> topCells;
        std::vector<std::pair<Position, uint32_t>> enemyTopCells;

        topCells = evaluator.evaluateBoard(board, CellState::Player1, 5);
        enemyTopCells = evaluator.evaluateBoard(board, CellState::Player2, 5);


        // SendBest case scenario for both players
        std::for_each(topCells.cbegin(),
                      topCells.cend(),
                      [&outCases, &board, &round](std::pair<Position, uint32_t> const &cell) {
                          outCases.push_back(
                                  std::make_unique<ai::MonteCarloCase>(board, cell.first.x, cell.first.y, round)
                          );
                      });
        std::for_each(enemyTopCells.cbegin(),
                      enemyTopCells.cend(),
                      [&outCases, &board, &round](std::pair<Position, uint32_t> const &cell) {
                          outCases.push_back(
                                  std::make_unique<ai::MonteCarloCase>(board, cell.first.x, cell.first.y, round)
                          );
                      });
    }

    void MonteCarloIA::resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) {
        double max = -1.0;

        for (auto const &oneCase : casesDone) {
            if (max < (*oneCase).getWeight()) {
                max = (*oneCase).getWeight();
                posOut = (*oneCase).getPos();
            }
        }
    }
}