cmake_minimum_required(VERSION 3.8)

set(NAME HiShinUnit)

project(${NAME})

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES
        src/main.cpp
        src/Core/Core.cpp
        include/Core/Core.hpp
        src/Core/TaskManager.cpp
        include/Core/TaskManager.hpp
        src/Tools/Splitter.cpp
        include/Tools/Splitter.hpp
        include/Logic/Cell.hpp
        src/Logic/Board.cpp
        include/Logic/Board.hpp
        src/MonteCarlo/Checker.cpp
        include/MonteCarlo/Checker.hpp
        include/Tools/Singleton.hpp
        src/Core/ThreadPool.cpp
        include/Core/ThreadPool.hpp
        src/Logic/AICase.cpp
        include/Logic/AICase.hpp
        include/Core/ThreadState.hpp
        include/Logic/Position.hpp
        src/Logic/AAI.cpp
        include/Logic/AAI.hpp
        include/Logic/Position.hpp
        src/MonteCarlo/MonteCarloIA.cpp
        include/MonteCarlo/MonteCarloIA.hpp
        src/MonteCarlo/MonteCarloCase.cpp
        include/MonteCarlo/MonteCarloCase.hpp
        src/Shin/Evaluator/Evaluator.cpp
        include/Shin/Evaluator/Evaluator.hpp
        include/Shin/Evaluator/Move.h
        src/Logic/Position.cpp
        src/Shin/Evaluator/Line.cpp
        include/Shin/Evaluator/Line.hpp
        src/MonteCarlo/CanIProcess.cpp
        include/MonteCarlo/CanIProcess.hpp
        src/Shin/ShinAI.cpp
        include/Shin/ShinAI.hpp
        src/Shin/ShinCase.cpp
        include/Shin/ShinCase.hpp src/Shin/ShinHalbard.cpp include/Shin/ShinHalbard.hpp)

add_executable(${NAME} ${SOURCE_FILES})