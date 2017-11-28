//
// Created by 53818 on 27/11/2017.
//

#include <algorithm>
#include <iostream>
#include "TaskManager.hpp"

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
            std::remove(out.begin(), out.begin() + 1, out[0]);
        }
        return (*this.*tasks[proceed])(out);
    }
    return "ERROR";
}

std::string TaskManager::start(std::vector<std::string> const &args) const {
    if (args.size() != 1)
        return MSG_ERROR + "missing size argument";

    if (std::stoi(args[0]) != size)
        return MSG_ERROR + "size not supported";

    return MSG_OK;
}

std::string TaskManager::turn(std::vector<std::string> const &args) const {
    return "0,0";
}

std::string TaskManager::begin(std::vector<std::string> const &args) const {
    return "0,0";
}

std::string TaskManager::unknown(std::vector<std::string> const &args) const {
    return MSG_UNKNOWN;
}

std::string TaskManager::configure(std::vector<std::string> const &args) const {
    return std::string();
}

bool TaskManager::isBoardInConfigurationMode() const {
    return isBoardInConfiguration;
}



TaskManager::TaskManager(uint32_t boardSize):
        tasks({
                      {"START", &TaskManager::start},
                      {"BEGIN", &TaskManager::begin},
                      {"INFO", &TaskManager::unknown},
                      {"BOARD", &TaskManager::unknown},
                      {"DONE", &TaskManager::unknown},
                      {"TURN", &TaskManager::turn},
                      {"END", &TaskManager::end},
                      {"ABOUT", &TaskManager::unknown},
                      {"RECTSTART", &TaskManager::unknown},
                      {"RESTART", &TaskManager::unknown},
                      {"TAKEBACK", &TaskManager::unknown},
                      {"PLAY", &TaskManager::unknown},
                      {"ABOUT", &TaskManager::unknown},
                      {"CONFIGURE", &TaskManager::configure}
              }),
        splitter(),
        size(boardSize)
{
}

std::string TaskManager::end() {
    return "END";
}

