#pragma once
#include "Liquid.h"

class Water : public Liquid
{
public:
	virtual std::string getType() override { return "Water"; }
	virtual sf::Color getColour() override { return sf::Color(0, 0, 205); };
	virtual bool update(sf::Vector2i position, Chunk* chunk);
};