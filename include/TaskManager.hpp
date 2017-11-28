//
// Created by 53818 on 27/11/2017.
//

#ifndef GOMOKU_PARSER_H
#define GOMOKU_PARSER_H

#include <string>
#include <map>
#include <functional>
#include <vector>
#include <memory>
#include "Splitter.hpp"
#include "Board.hpp"

class TaskManager {
public:
    explicit TaskManager(bool &running, uint32_t boardSize = 18);
    ~TaskManager() = default;

    std::string executeTask(std::string const &task);

    typedef std::string (TaskManager::*taskPtr_t)(std::vector<std::string> const &);

private:
    std::map<std::string, taskPtr_t> tasks;
    Splitter splitter;
    uint32_t size;
    bool isBoardInConfiguration = false;
    bool &coreRunning;
    std::unique_ptr<Board> board;

    std::string const MSG_ERROR = "ERROR";
    std::string const MSG_UNKNOWN = "UNKNOWN";
    std::string const MSG_OK = "OK";
    std::string const MSG_NO_RESPONSE = "";
    std::string const MSG_ABOUT = R"(name="HiShinUnit", version="1.0", authors="Marc, Benjamin, Pierre", country="France")";

    std::string start(std::vector<std::string> const& args);
    std::string turn(std::vector<std::string> const& args);
    std::string begin(std::vector<std::string> const& args);
    std::string boardUp(std::vector<std::string> const& args);
    std::string configure(std::vector<std::string> const& args);
    std::string done(std::vector<std::string> const& args);
    std::string unknown(std::vector<std::string> const& args);
    std::string rectstart(std::vector<std::string> const& args);
    std::string restart(std::vector<std::string> const& args);
    std::string about(std::vector<std::string> const& args);
    std::string takeBack(std::vector<std::string> const& args);
    std::string end(std::vector<std::string> const& args);
    bool isInBound(int x) const;

};

#endif //GOMOKU_PARSER_H
