//
// Created by Pierre Bougon on 28/11/2017.
//

#ifndef GOMOKU_AICASE_HPP_
#define GOMOKU_AICASE_HPP_


#include <memory>
#include "Board.hpp"

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
        AICase();
        AICase(AICase const &other) = delete;
        AICase(std::unique_ptr<Board> newBoard, size_t round);

        void        setBoard(std::unique_ptr<Board> newBoard);

        size_t      getRound() const;
        void        setRound(size_t round);

        void        resetWeight();
        double      getWeight();

        virtual void process() = 0;

        AICase &operator=(AICase const &other) = delete;

    protected:
        std::unique_ptr<Board>  board;
        double                  weight;
        size_t                  round;
    };
}


#endif // !GOMOKU_AICASE_HPP_
