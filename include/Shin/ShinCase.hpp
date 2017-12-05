//
// Created by 53818 on 04/12/2017.
//

#ifndef PBRAIN_HISHINUNIT_SHINCASE_HPP
#define PBRAIN_HISHINUNIT_SHINCASE_HPP

#include "Shin/Evaluator/Evaluator.hpp"
#include "Logic/AICase.hpp"

namespace ai {
    class ShinCase : public AICase {
    public:
        void process() override;
        ShinCase(Board const &board, uint32_t x, uint32_t y, size_t round, CellState player);
        Position const &operator*() const;

    private:
        Evaluator evaluator;

        // Deleted Constructors and operators
    public:
        ShinCase() = delete;
        ShinCase(ShinCase const &) = delete;
        ShinCase(ShinCase &&) = delete;
        ShinCase &operator=(ShinCase const &) = delete;
        ShinCase &operator=(ShinCase &&) = delete;
    };
}

#endif //PBRAIN_HISHINUNIT_SHINCASE_HPP
