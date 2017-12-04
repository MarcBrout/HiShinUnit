//
// Created by Pierre Bougon on 25/04/17.
//

#ifndef CPP_ZAPPY_SINGLETON_HPP_
#define CPP_ZAPPY_SINGLETON_HPP_

#include <iostream>
#include <vector>

template <typename T>
class Singleton
{
public:
    virtual ~Singleton(){};
    static T &getInstance()
    {
      static T instance;
      return instance;
    }
    T &operator=(const T &) = delete;
};

#endif // !CPP_ZAPPY_SINGLETON_HPP_
