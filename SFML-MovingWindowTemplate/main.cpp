#include "Simulation.h"
#include <string>
#include <iostream>


int main()
{
	sf::Vector2u screenSize(1920, 1080);
	Simulation sim(screenSize);
	sim.run();
	return 0;
}