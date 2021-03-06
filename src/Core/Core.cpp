//
// Created by 53818 on 27/11/2017.
//

#include <iostream>
#include "Shin/ShinAI.hpp"
#include "Core/TaskManager.hpp"
#include "Core/Core.hpp"

static const unsigned int max_threads = std::thread::hardware_concurrency();

namespace ai {
    void Core::run() {
        TaskManager taskManager(running, 19, std::make_unique<ai::ShinAI>(max_threads > 0 ? max_threads : 4, 3000));

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
}