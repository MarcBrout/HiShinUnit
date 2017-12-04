//
// Created by 53818 on 27/11/2017.
//

#include <iostream>
#include "MonteCarlo/MonteCarloIA.hpp"
#include "Core/TaskManager.hpp"
#include "Core/Core.hpp"

void Core::run() {
    TaskManager taskManager(running, 19, std::make_unique<MonteCarloIA>());

    while (running) {
        std::string line = readString();

        if (std::cin.eof())
            break;

        std::string answer = taskManager.executeTask(line);

        if (!answer.empty())
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
