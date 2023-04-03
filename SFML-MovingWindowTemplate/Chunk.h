#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include <iostream>

class Chunk
{
public:
	Chunk(int x, int y, std::map<std::pair<int, int>, Chunk*>&);
	~Chunk();

	bool update();
	void updateImage(sf::Image& img, sf::Vector2f windowPosition, sf::Vector2f windowSize);
	bool isVisible(sf::Vector2f windowPosition,sf::Vector2f windowSize);
	Chunk* getChunk(sf::Vector2i chunkPosition);
	sf::Vector2i getChunkPosition() { return chunkPosition; }
	void spawnCell(CellTypes cellType, sf::Vector2i mousePosition);
	// Cells number control
	void increaseCellNumber() { cellNumber++; }
	void decreaseCellNumber() { cellNumber--; }
	// Active chunk control
	void wakeUpChunk() { activeChunk = 2; }
	bool isActive() { return activeChunk; }
public:
	static int getSize() { return chunkSize; }
	static int getMaxX() { return maxChunkX; }
	static int getMaxY() { return maxChunkY; }
public:
	std::vector<std::vector<Cell*>> cellVec;
private:
	sf::Vector2i chunkPosition;
	std::map<std::pair<int, int>, Chunk*>& chunkMap;
	// Chunk elements
	int activeChunk;
	int cellNumber;
	static const int chunkSize = 180;
	static const int maxChunkX = 5;
	static const int maxChunkY = 5;
};