//
// Created by 53818 on 04/12/2017.
//

#ifndef PBRAIN_HISHINUNIT_SHINAI_HPP
#define PBRAIN_HISHINUNIT_SHINAI_HPP

#include "Logic/AAI.hpp"

namespace ai {
    class ShinAI : AAI {
        virtual ~ShinAI() = default;
        void initializeCases(Board const &board, std::deque<std::unique_ptr<ai::AICase>> &outCases, size_t round) override;
        void resolve(std::deque<std::unique_ptr<ai::AICase>> &casesDone, Position &posOut) override;
    };
}

#endif //PBRAIN_HISHINUNIT_SHINAI_HPP
