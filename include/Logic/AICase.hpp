//
// Created by Pierre Bougon on 28/11/2017.
//

#ifndef GOMOKU_AICASE_HPP_
#define GOMOKU_AICASE_HPP_


#include <memory>
#include "Board.hpp"
#include "Position.hpp"

namespace ai
{
    /**
     * This class represent the board on the state n + 1
     * With this configuration we wil explore multiple ways
     * And then define the weight of this case
     * Finally we will choose the case with the most weight points
     */
    class AICase
    {
    public:
        /**
         * AICase Constructors
         * @param newBoard Copy of the board, it will be used to process the case
         * @param x position of the Cell being processed
         * @param y position of the Cell being processed
         * @param round of the game
         * @param player to whow belong the case
         */
        AICase(std::unique_ptr<Board> newBoard,
               uint32_t x,
               uint32_t y,
               size_t round,
               CellState player = CellState::Player1);
        virtual ~AICase() = default;

        /**
         * Method used to process and resolve the AICase
         */
        virtual void process() = 0;

        /**
         * Getter
         * @return the processed value of the case attribued by the process method
         */
        double getWeight();

        // Getters and setters
        void setBoard(std::unique_ptr<Board> newBoard);
        size_t getRound() const;
        const Position &getPos() const;
        void setRound(size_t round);
        void resetWeight();
        CellState   getPlayer() const;

    protected:
        std::unique_ptr<Board>  board;
        double                  weight;
        size_t                  round;
        Position                pos;
        CellState               player;

        // Delete constructors and operators
    public:
        AICase() = delete;
        AICase(AICase const &) = delete;
        AICase(AICase &&) = delete;
        AICase &operator=(AICase const&) = delete;
        AICase &operator=(AICase &&) = delete;
    };
}


#endif // !GOMOKU_AICASE_HPP_
