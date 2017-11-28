//
// Created by Pierre Bougon on 03/02/17.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "tools/Logger.hpp"

#ifdef DEBUG
bool Debug::DEBUG_MODE = true;
#else
bool Debug::DEBUG_MODE = false;
#endif

Logger::~Logger() {

}

Logger::Logger() : outFile("")
{

}

void Logger::log(Logger::Level lvl, std::string msg, bool abort)
{
    switch (lvl)
    {
        case Logger::_DEBUG_:
            if (Debug::DEBUG_MODE)
                std::cout << "<Debug> : " << msg << std::endl;
            break;
        case Logger::INFO:
            std::cout << "<Info> : " << msg << std::endl;
            break;
        case Logger::WARNING:
            std::cerr << "<Warning> : " << msg << std::endl;
            break;
        case Logger::ERROR:
            std::cerr << "<Error> : " << msg << std::endl;
            if (abort)
                std::abort();
            break;
        case Logger::NONE:
            break;
    }
}

void Logger::log(std::string msg, Logger::Level lvl)
{
    if (lvl == Logger::Level::NONE)
        std::cout << msg << std::endl;
    else
        std::cout << toString(lvl) << ": " << msg << std::endl;
}

void Logger::logFile(std::string msg, Logger::Level lvl)
{
    std::ostream &stream = outFile.is_open() ? outFile : std::cout;
    stream << toString(lvl) << ": " << msg << std::endl;
}

std::string Logger::toString(Logger::Level lvl)
{
    static const char* const buffer[] = {  "_DEBUG_", "INFO", "WARNING", "ERROR", "" };
    return buffer[lvl];
}

void Logger::setFile(std::string const &file)
{
    if (file != "") {
        outFile.open(file.c_str());
    }
}

void Logger::closeFile()
{
    if (outFile.is_open())
        outFile.close();
}
