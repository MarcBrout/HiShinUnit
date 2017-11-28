cmake_minimum_required(VERSION 3.8)
project(gomoku)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES
        src/main.cpp
        src/Core.cpp
        include/Core.h
        src/TaskManager.cpp
        include/TaskManager.h
        src/Splitter.cpp
        include/Splitter.hpp
        include/Cell.h
        src/Board.cpp
        include/Board.h
        src/Checker.cpp
        include/Checker.h
        include/Logger.h
        src/Logger.cpp)

add_executable(gomoku ${SOURCE_FILES})