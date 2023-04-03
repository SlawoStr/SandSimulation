#pragma once
#include "MoveableSolid.h"

class Sand : public MoveableSolid
{
public:
	virtual std::string getType() override {return "Sand"; }
	virtual sf::Color getColour() override {return sf::Color(255, 255, 102);}
	virtual bool update(sf::Vector2i position, Chunk* chunk);
};