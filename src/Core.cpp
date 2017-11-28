//
// Created by 53818 on 27/11/2017.
//

#include <iostream>
#include "TaskManager.hpp"
#include "Core.hpp"

void Core::run() {
    TaskManager taskManager;

    while (running) {
        std::string line = readString();

        std::string answer = taskManager.executeTask(line);

        send(answer);
    }
}

std::string Core::readString() const {
    std::string line;

    std::getline(std::cin, line);
    return line;
}

void Core::send(std::string const &message) const {
    std::cout << message << std::endl;
}
