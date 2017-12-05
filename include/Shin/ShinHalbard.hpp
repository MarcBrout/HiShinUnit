//
// Created by 53818 on 05/12/2017.
//

#ifndef PBRAIN_HISHINUNIT_SHINHALBARD_HPP
#define PBRAIN_HISHINUNIT_SHINHALBARD_HPP

#include <vector>
#include <memory>
#include <string>
#include "Logic/AICase.hpp"
#include "Evaluator/Line.hpp"

namespace ai {
    class ShinCase;

    class ShinHalbard {
    public:
        void addCase(std::unique_ptr<ai::AICase> &victim);
        uint32_t getCount(Line::Values value);
        std::vector<Position> getMaxPositions(Line::Values value, Line::Values &maxOut);
        void clear();
        void print(const std::string &str);

    private:
        std::vector<std::unique_ptr<ai::AICase>> finalWins;
        std::vector<std::unique_ptr<ai::AICase>> wins;
        std::vector<std::unique_ptr<ai::AICase>> others;

        std::vector<Position> setMaxPositions(std::vector<std::unique_ptr<ai::AICase>> &cases, Line::Values &outMax);
    };
}

#endif //PBRAIN_HISHINUNIT_SHINHALBARD_HPP
