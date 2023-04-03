#pragma once
#include "MoveableSolid.h"

class Stone : public MoveableSolid
{
public:
	virtual std::string getType() override { return "Stone"; };
	virtual sf::Color getColour() override { return sf::Color(192, 192, 192); }
	virtual bool update(sf::Vector2i position, Chunk* chunk);
};