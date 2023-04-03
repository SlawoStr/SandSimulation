#pragma once
#include "Chunk.h"
#include "Cell.h"

class ChunkManager
{
public:
	ChunkManager();
	void update(sf::Image& image, sf::Vector2f windowPosition, sf::Vector2f windowSize);
	void spawnCell(CellTypes cellType, sf::Vector2f mousePosition);
	void draw(sf::RenderTarget& target);
private:
	std::map<std::pair<int, int>, Chunk*> gameMap;
};