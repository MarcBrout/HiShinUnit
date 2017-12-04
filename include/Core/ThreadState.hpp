//
// Created by Pierre Bougon on 28/11/2017.
//

#ifndef GOMOKU_THREADSTATE_HPP_
#define GOMOKU_THREADSTATE_HPP_

enum class ThreadState : unsigned char
{
    sleeping = 0,
    working
};

#endif // !GOMOKU_THREADSTATE_HPP_
