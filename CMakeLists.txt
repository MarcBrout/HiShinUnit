cmake_minimum_required(VERSION 3.8)

set(NAME pbrain-HiShinUnit)

project(${NAME})

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
        include/Singleton.hpp
        src/ThreadPool.cpp
        include/ThreadPool.hpp
        src/AICase.cpp
        include/AICase.hpp
        include/ThreadState.hpp
        include/Position.hpp
        src/AAI.cpp
        include/AAI.hpp
        include/Position.hpp
        src/MonteCarloIA.cpp
        include/MonteCarloIA.hpp src/MonteCarloCase.cpp include/MonteCarloCase.hpp src/Evaluator/Evaluator.cpp include/Evaluator/Evaluator.hpp include/Evaluator/Move.h src/Position.cpp src/Evaluator/Point.cpp include/Evaluator/Point.hpp)

add_executable(${NAME} ${SOURCE_FILES})