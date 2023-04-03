#pragma once
#include <SFML/Graphics.hpp>
#include "CollisionMap.h"

enum class CellTypes
{
	STONE,
	WATER,
	GAS,
	SAND,
	EMPTY
};


class Chunk;

class Cell
{
public:
	virtual std::string getType() = 0;
	virtual sf::Color getColour() = 0;
	virtual bool update(sf::Vector2i position,Chunk * chunk) = 0;
	bool isUpdated() { return updated; }
	void resetCell() { updated = false; }
	void updateCell() { updated = true; }
protected:
	bool updated = false;
};