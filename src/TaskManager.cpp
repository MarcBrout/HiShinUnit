//
// Created by 53818 on 27/11/2017.
//

#include <algorithm>
#include <Logger.hpp>
#include "TaskManager.hpp"

std::string TaskManager::executeTask(std::string const &task) {
    std::vector<std::string> out;

    Logger::getInstance().logFile("task = " + task);
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

        for (std::string const &str: out)
            Logger::getInstance().logFile("task args = " + str);

        Logger::getInstance().logFile("command to proceed = " + proceed);
        if (tasks.find(proceed) == tasks.end())
            return MSG_UNKNOWN;
        return (*this.*tasks[proceed])(out);
    }
    return MSG_ERROR;
}

std::string TaskManager::start(std::vector<std::string> const &args) const {
    if (args.size() != 1)
        return MSG_ERROR + " expecting only board size (18)";

    if (std::stoi(args[0]) != size)
        return MSG_ERROR + " size not supported (18)";

    board = std::make_unique();

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

TaskManager::TaskManager(bool &running, uint32_t boardSize):
        tasks({
                      {"START", &TaskManager::start},
                      {"BEGIN", &TaskManager::begin},
                      {"INFO", &TaskManager::unknown},
                      {"BOARD", &TaskManager::unknown},
                      {"DONE", &TaskManager::unknown},
                      {"TURN", &TaskManager::turn},
                      {"END", &TaskManager::unknown},
                      {"ABOUT", &TaskManager::unknown},
                      {"RECTSTART", &TaskManager::unknown},
                      {"RESTART", &TaskManager::unknown},
                      {"TAKEBACK", &TaskManager::unknown},
                      {"PLAY", &TaskManager::unknown},
                      {"ABOUT", &TaskManager::unknown},
                      {"CONFIGURE", &TaskManager::configure}
              }),
        splitter(),
        size(boardSize),
        coreRunning(running)
{
}

