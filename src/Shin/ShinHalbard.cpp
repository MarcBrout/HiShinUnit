//
// Created by 53818 on 05/12/2017.
//

#include <unordered_map>
#include <iostream>
#include "Shin/ShinHalbard.hpp"

void ai::ShinHalbard::addCase(std::unique_ptr<ai::AICase> &victim) {
    auto value = static_cast<uint32_t>((*victim).getWeight());

    switch (value) {
        case Line::FINAL_WIN:
            finalWins.push_back(std::move(victim));
            break;
        case Line::WIN:
            wins.push_back(std::move(victim));
            break;
        default:
            others.push_back(std::move(victim));
            break;
    }
}

uint32_t ai::ShinHalbard::getCount(ai::Line::Values value) {
    uint32_t size = 0;

    switch (value) {
        case Line::FINAL_WIN:
            size = finalWins.size();
            break;
        case Line::WIN:
            size = wins.size();
            break;
        default:
            size = others.size();
            break;
    }
    return (size);
}

std::vector<Position> ai::ShinHalbard::getMaxPositions(Line::Values value, Line::Values &maxOut) {
    switch (value) {
        case Line::FINAL_WIN:
            return setMaxPositions(finalWins, maxOut);
        case Line::WIN:
            return setMaxPositions(wins, maxOut);
        default:
            return setMaxPositions(others, maxOut);
    }
}

std::vector<Position>
ai::ShinHalbard::setMaxPositions(std::vector<std::unique_ptr<ai::AICase>> &cases, Line::Values &outMax) {
    std::vector<Position> maxes;

    if (!cases.empty()) {
        std::sort(cases.begin(), cases.end(), [](std::unique_ptr<ai::AICase> &a,
                                                 std::unique_ptr<ai::AICase> &b) {
            return ((*a).getWeight() > (*b).getWeight());
        });

        outMax = static_cast<Line::Values>(static_cast<uint32_t>((*cases.front()).getWeight()));

        //std::cout << "DEBUG Selecting max values" << std::endl;
        for (std::unique_ptr<ai::AICase> const &Case : cases) {
            if ((*Case).getWeight() == (*cases.front()).getWeight()) {
                //std::cout << "DEBUG Position [" << (*Case).getPos().y << "][" << (*Case).getPos().x << "]" << std::endl;
                maxes.emplace_back(Position((*Case).getPos()));
            } else {
                break;
            }
        }
    }
    return maxes;
}

void ai::ShinHalbard::clear() {
    finalWins.clear();
    wins.clear();
    others.clear();
}

void printLine(const std::string &str, const std::vector<std::unique_ptr<ai::AICase>> &line) {
    std::cout << "DEBUG value : " + str << ", count :" << line.size() << std::endl;

    for (std::unique_ptr<ai::AICase> const &Case : line) {
        std::cout << "DEBUG cell[" << (*Case).getPos().y << "][" << (*Case).getPos().x << "] = " << (*Case).getWeight() << std::endl;
    }
}

void ai::ShinHalbard::print(const std::string &str) {
    std::cout << "DEBUG halbard : " + str << std::endl;

    printLine("FINAL_WINS", finalWins);
    printLine("WINS", wins);
    printLine("OTHERS", others);
}
