//
// Created by 53818 on 27/11/2017.
//

#include <algorithm>
#include <iostream>
#include "Logic/Position.hpp"
#include "Core/TaskManager.hpp"

namespace ai {
    std::string TaskManager::executeTask(std::string const &task) {
        std::vector<std::string> out;

        splitter.clear();
        splitter.split(task, " ,");
        splitter.moveTokensTo(out);

        std::string proceed;
        if (!out.empty()) {
            if (isBoardInConfiguration) {
                proceed = "CONFIGURE";
            } else {
                proceed = out.front();
                out.erase(out.begin());
            }

            if (tasks.find(proceed) == tasks.end())
                return MSG_UNKNOWN;
            return (*this.*tasks[proceed])(out);
        }
        return MSG_ERROR;
    }

    std::string TaskManager::start(std::vector<std::string> const &args) {
        if (args.size() != 1)
            return MSG_ERROR + " expecting only board size (18)";

        if (std::stoi(args[0]) != size)
            return MSG_ERROR + " size not supported (18)";

        return MSG_OK;
    }

    std::string TaskManager::turn(std::vector<std::string> const &args) {
        if (args.size() != 2)
            return MSG_ERROR + " expecting TURN with format TURN [x],[y]";
        auto x = static_cast<uint32_t >(std::stoi(args[0]));
        auto y = static_cast<uint32_t >(std::stoi(args[1]));

        if ((x < 0 || x > size) || (y < 0 || y > size))
            return MSG_ERROR + " expecting x and y in range 0..18";
        (*board).setCellState(x, y, Player2);

        Position pos;
        (*ai).getAIPlay(*board, currentRound++, pos);

        (*board).setCellState(pos.x, pos.y, Player1);
        return pos.toString();
    }

    std::string TaskManager::begin(std::vector<std::string> const &args) {
        Position pos;
        (*ai).getAIPlay(*board, currentRound++, pos);

        (*board).setCellState(pos.x, pos.y, Player1);
        return pos.toString();
    }

    std::string TaskManager::boardUp(std::vector<std::string> const &args) {
        (*board).reset();
        isBoardInConfiguration = true;
        currentRound = 0;
        return MSG_NO_RESPONSE;
    }

    std::string TaskManager::configure(std::vector<std::string> const &args) {
        if (args.size() == 3) {
            auto x = static_cast<uint32_t>(std::stoi(args[0]));
            auto y = static_cast<uint32_t>(std::stoi(args[1]));
            auto p = static_cast<uint32_t>(std::stoi(args[2]));

            if (isInBound(x) && isInBound(y) && (p == 1 || p == 2)) {
                (*board).setCellState(x, y, static_cast<CellState>(p));
            }
        }

        return MSG_NO_RESPONSE;
    }

    std::string TaskManager::done(std::vector<std::string> const &args) {
        Position pos;

        (*ai).getAIPlay(*board, currentRound++, pos);
        isBoardInConfiguration = false;

        (*board).setCellState(pos.x, pos.y, Player1);
        return pos.toString();
    }

    std::string TaskManager::unknown(std::vector<std::string> const &args) {
        return MSG_UNKNOWN;
    }

    std::string TaskManager::about(std::vector<std::string> const &args) {
        return MSG_ABOUT;
    }

    std::string TaskManager::restart(std::vector<std::string> const &args) {
        (*board).reset();
        return MSG_OK;
    }

    std::string TaskManager::end(std::vector<std::string> const &args) {
        coreRunning = false;
        return MSG_NO_RESPONSE;
    }

    std::string TaskManager::takeBack(std::vector<std::string> const &args) {
        if (args.size() != 2)
            return MSG_ERROR + " expecting TURN with format TAKEBACK [x],[y]";
        auto x = static_cast<uint32_t >(std::stoi(args[0]));
        auto y = static_cast<uint32_t >(std::stoi(args[1]));

        if ((x < 0 || x > size) || (y < 0 || y > size))
            return MSG_ERROR + " expecting x and y in range 0..18";
        (*board).setCellState(x, y, Empty);
        return "OK";
    }

    std::string TaskManager::rectstart(std::vector<std::string> const &args) {
        return MSG_ERROR + " rectangular board are not supported";
    }

    bool TaskManager::isInBound(int x) const {
        return (x < 19 && x >= 0);
    }

    TaskManager::TaskManager(bool &running,
                             uint32_t boardSize,
                             std::unique_ptr<AAI> myAi) :
            tasks({
                          {"START",     &TaskManager::start},
                          {"BEGIN",     &TaskManager::begin},
                          {"INFO",      &TaskManager::noMessage},
                          {"BOARD",     &TaskManager::boardUp},
                          {"DONE",      &TaskManager::done},
                          {"TURN",      &TaskManager::turn},
                          {"END",       &TaskManager::end},
                          {"RECTSTART", &TaskManager::rectstart},
                          {"RESTART",   &TaskManager::restart},
                          {"TAKEBACK",  &TaskManager::takeBack},
                          {"PLAY",      &TaskManager::unknown},
                          {"ABOUT",     &TaskManager::about},
                          {"CONFIGURE", &TaskManager::configure}
                  }),
            splitter(),
            size(boardSize),
            isBoardInConfiguration(false),
            coreRunning(running),
            board(std::make_unique<Board>()),
            ai(std::move(myAi)),
            currentRound(0) {
    }

    std::string TaskManager::noMessage(std::vector<std::string> const &args) {
        return MSG_NO_RESPONSE;
    }

    TaskManager::~TaskManager() {
        ai->stop();
    }
}