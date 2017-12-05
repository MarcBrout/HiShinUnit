//
// Created by 53818 on 04/12/2017.
//

#ifndef PBRAIN_HISHINUNIT_SHINAI_HPP
#define PBRAIN_HISHINUNIT_SHINAI_HPP

#include "Shin/Evaluator/Line.hpp"
#include "ShinHalbard.hpp"
#include "Logic/AAI.hpp"

namespace ai {
    class ShinAI : public AAI {
    public:
        ShinAI(unsigned int threadCount, unsigned int timeLimit);
        ~ShinAI() override = default;

    private:
        ShinHalbard myPlays;
        ShinHalbard enemyPlays;

        void initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases, size_t round) override;
        void resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) override;
        void fusionPlays(Position &outPos, Line::Values value, CellState priority);
        void simplePlay(Position &outPos, Line::Values value, ShinHalbard &halbard);
    };
}

#endif //PBRAIN_HISHINUNIT_SHINAI_HPP
