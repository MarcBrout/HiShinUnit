#include "Core/Core.hpp"
#include <ctime>

int main()
{
    std::srand(static_cast<unsigned int>(time(nullptr)));
    Core().run();
	return 0;
}