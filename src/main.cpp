#include "Core/Core.hpp"
#include <ctime>

int main()
{
    std::srand(static_cast<unsigned int>(time(nullptr)));
    ai::Core().run();
	return 0;
}