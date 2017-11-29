cmake_minimum_required(VERSION 3.8)
project(gomoku)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES
        src/main.cpp
        src/Core.cpp
        include/Core.hpp
        src/TaskManager.cpp
        include/TaskManager.hpp
        src/Splitter.cpp
        include/Splitter.hpp
        include/Cell.hpp
        src/Board.cpp
        include/Board.hpp
        src/Checker.cpp
        include/Checker.hpp
        include/Logger.hpp
        include/Singleton.hpp
        src/Logger.cpp
        src/ThreadPool.cpp
        include/ThreadPool.hpp
        src/AICase.cpp
        include/AICase.hpp
        include/ThreadState.hpp
        include/Position.hpp
        include/ThreadState.hpp
        include/Position.hpp src/AAI.cpp include/AAI.hpp)

add_executable(gomoku ${SOURCE_FILES})