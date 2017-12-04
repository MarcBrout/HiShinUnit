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
        AICase();
        AICase(AICase const &other) = delete;
        AICase(std::unique_ptr<Board> newBoard, size_t round);
        AICase(std::unique_ptr<Board> newBoard, uint32_t x, uint32_t y, size_t round);
        virtual ~AICase() = default;

        void        setBoard(std::unique_ptr<Board> newBoard);
        size_t      getRound() const;
        const Position &getPos() const;
        void        setRound(size_t round);
        double      getWeight();

        void        resetWeight();
        virtual void process() = 0;

        AICase &operator=(AICase const &other) = delete;

    protected:
        std::unique_ptr<Board>  board;
        double                  weight;
        size_t                  round;
        Position                pos;
    };
}


#endif // !GOMOKU_AICASE_HPP_
