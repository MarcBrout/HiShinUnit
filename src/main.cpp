#include "Core.hpp"
#include "Logger.hpp"

int main()
{
    Logger::getInstance().setFile("log.txt");
    Core().run();
	return 0;
}