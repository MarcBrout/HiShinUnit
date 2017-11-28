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
    explicit TaskManager(uint32_t boardSize = 18);
    ~TaskManager() = default;

    std::string executeTask(std::string const &task);
    bool isBoardInConfigurationMode() const;

    typedef std::string (TaskManager::*taskPtr_t)(std::vector<std::string> const &) const;

private:
    std::map<std::string, taskPtr_t> tasks;
    Splitter splitter;
    uint32_t size;
    bool isBoardInConfiguration = false;

    std::string const MSG_ERROR = "ERROR";
    std::string const MSG_UNKNOWN = "UNKNOWN";
    std::string const MSG_OK = "OK";

    std::string start(std::vector<std::string> const& args) const;
    std::string turn(std::vector<std::string> const& args) const;
    std::string begin(std::vector<std::string> const& args) const;
    std::string configure(std::vector<std::string> const& args) const;
    std::string unknown(std::vector<std::string> const& args) const;
};

#endif //GOMOKU_PARSER_H
