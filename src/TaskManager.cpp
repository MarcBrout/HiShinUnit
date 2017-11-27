//
// Created by 53818 on 27/11/2017.
//

#include <algorithm>
#include "TaskManager.h"

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
    return std::string();
}

std::string TaskManager::unknown(std::vector<std::string> const &args) const {
    return "UNKNOWN";
}

std::string TaskManager::configure(std::vector<std::string> const &args) const {
    return std::string();
}

bool TaskManager::isBoardInConfigurationMode() const {
    return isBoardInConfiguration;
}

TaskManager::TaskManager(): tasks({
                {"START", &start},
                {"BEGIN", &unknown},
                {"INFO", &unknown},
                {"BOARD", &unknown},
                {"DONE", &unknown},
                {"TURN", &unknown},
                {"END", &unknown},
                {"ABOUT", &unknown},
                {"RECTSTART", &unknown},
                {"RESTART", &unknown},
                {"TAKEBACK", &unknown},
                {"PLAY", &unknown},
                {"ABOUT", &unknown},
                {"CONFIGURE", &configure}
        }),
                            splitter()
{
}

