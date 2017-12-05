//
// Created by Marc on 02/12/2017.
//

#ifndef GOMOKU_EVALUATOR_HPP
#define GOMOKU_EVALUATOR_HPP

#include <map>
#include <memory>
#include <functional>
#include <vector>
#include "Logic/Board.hpp"
#include "Line.hpp"
#include "Logic/Position.hpp"

namespace ai {
    /**
     * Class used to evaluate the cells by the ShinAI
     */
    class Evaluator {
    public:
        /**
         * Method used to evaluate the board, it processes every cells.
         * @param board to be processed
         * @param player for whom we want to evaluate the cells value
         * @param limit of cases returned
         * @param minimumLvl of cases returned
         * @return the processed cases using the move semantics
         */
        std::vector<std::pair<Position, uint32_t>> evaluateBoard(Board const &board,
                                                                 CellState player,
                                                                 uint8_t limit = 10,
                                                                 uint32_t minimumLvl = Line::NONE);

        /**
         * Same Method as evaluateBoard but only process cells satisfying the check function and return
         * the best cell
         * @param board to be processed
         * @param outPos position of the best Cell
         * @param player for whom we want to evaluate the cells value
         * @param check function used to pick if a cell must be processed of not
         * @return the value of the best Cell
         */
        uint32_t evaluateBoard_max_if(const Board &board, Position &outPos, CellState player,
                                      const std::function<bool(Board const &, uint32_t const &,
                                                               uint32_t const &)> &check);
        /**
         * Same Method as evaluateBoard but only process cells satisfying the check function
         * @param board to be processed
         * @param outPos position of the best Cell
         * @param player for whom we want to evaluate the cells value
         * @param check function used to pick if a cell must be processed of not
         * @param limit of cases to be returned
         * @return the best cells satisfying the parameters
         */
        std::vector<std::pair<Position, uint32_t>> evaluateBoard_if(const Board &board, Position &outPos, CellState player,
                                                                    const std::function<bool(const Board &, const uint32_t &,
                                                                                             const uint32_t &)> &check,
                                                                    uint32_t limit = 5);
        /**
         * Method used to evaluate a single point
         * @param board to be processed
         * @param play cell to be evaluated
         * @param player for whom we want to evaluate the cell
         * @return the value of the evaluated cell
         */
        uint32_t evaluatePoint(Board const &board, Position const &play, CellState player) const;
    };
}
#endif //GOMOKU_EVALUATOR_HPP
