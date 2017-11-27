//
// Created by 53818 on 27/11/2017.
//

#ifndef GOMOKU_PARSER_H
#define GOMOKU_PARSER_H

#include <string>
#include <map>
#include <functional>
#include <vector>
#include "Splitter.hpp"

class TaskManager {
public:
    TaskManager();
    ~TaskManager() = default;

    std::string executeTask(std::string const &task);
    bool isBoardInConfigurationMode() const;

private:
    std::map<std::string,
            std::function<std::string(std::vector<std::string> const&)>> tasks;
    Splitter splitter;
    bool isBoardInConfiguration = false;

    std::string start(std::vector<std::string> const& args) const;
    std::string configure(std::vector<std::string> const& args) const;
    std::string unknown(std::vector<std::string> const& args) const;

};

#endif //GOMOKU_PARSER_H
