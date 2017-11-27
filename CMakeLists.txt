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
        include/Splitter.hpp)

add_executable(HiShinUnit ${SOURCE_FILES})