//
// Created by 53818 on 27/11/2017.
//

#ifndef GOMOKU_CORE_H
#define GOMOKU_CORE_H

#include <string>

class Core {
public:
    void run();

private:
    bool running = true;

    std::string readString() const;
    void send(std::string const &message) const;
};

#endif //GOMOKU_CORE_H