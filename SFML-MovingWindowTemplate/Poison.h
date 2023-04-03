#pragma once
#include "Gas.h"

class Poison : public Gas
{
public:
	virtual std::string getType() override { return "Poison"; }
	virtual sf::Color getColour() override { return sf::Color(107, 142, 35); }
	virtual bool update(sf::Vector2i position, Chunk* chunk) {}
};