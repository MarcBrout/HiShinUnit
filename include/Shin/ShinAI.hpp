//
// Created by 53818 on 04/12/2017.
//

#ifndef PBRAIN_HISHINUNIT_SHINAI_HPP
#define PBRAIN_HISHINUNIT_SHINAI_HPP

#include "Shin/Evaluator/Line.hpp"
#include "ShinHalbard.hpp"
#include "Logic/AAI.hpp"

namespace ai {
    /**
     * AI doing a Value evaluation of every cells, try to detect potential forks and cutting plays from the opponent
     */
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

        // Deleted Constructors and operators
    public:
        ShinAI() = delete;
        ShinAI(ShinAI const &) = delete;
        ShinAI(ShinAI &&) = delete;
        ShinAI &operator=(ShinAI const &) = delete;
        ShinAI &operator=(ShinAI &&) = delete;
    };
}

#endif //PBRAIN_HISHINUNIT_SHINAI_HPP
