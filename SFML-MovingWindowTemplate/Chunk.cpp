#include "Chunk.h"
#include <iostream>
#include "CollisionMapping.h"


Chunk::Chunk(int x, int y, std::map<std::pair<int, int>, Chunk*>& chunkMap) : chunkPosition(x,y),chunkMap(chunkMap)
{
	static bool initialized;
	if (!initialized) {
		initialized = true;
		std::cout << "Once" << std::endl;
	}

	// Prepare space for cells
	cellVec.resize(chunkSize);
	for (int i = 0; i < chunkSize; i++)
	{
		cellVec[i].resize(chunkSize);
	}
	// Chunk elements
	cellNumber = 0;
	activeChunk = 2;
}

Chunk::~Chunk()
{
	for (int i = 0; i < cellVec.size(); i++)
	{
		for (int j = 0; j < cellVec[i].size(); j++)
		{
			delete cellVec[i][j];
		}
	}
}

bool Chunk::update()
{
	if (cellNumber == 0)
	{
		return false;
	}
	if (activeChunk)
	{
		int updated = 0;
		for (int i = 0; i < cellVec.size(); i++)
		{
			for (int j = 0; j < cellVec[i].size(); j++)
			{
				if (cellVec[i][j] != nullptr && cellVec[i][j]->isUpdated() == false)
				{
					if (cellVec[i][j]->update(sf::Vector2i(j, i), this))
					{
						updated++;

						if (i == 0 || i == 1)
						{
							sf::Vector2i nextPosition = chunkPosition;
							nextPosition.x *= chunkSize;
							nextPosition.y = (nextPosition.y - 1) * chunkSize;
							if (Chunk* nextChunk = getChunk(nextPosition))
							{
								nextChunk->wakeUpChunk();
							}
							if (j == 0 || j == 1)
							{
								sf::Vector2i nextPosition = chunkPosition;
								nextPosition.x = (nextPosition.x - 1) * chunkSize;;
								nextPosition.y = (nextPosition.y - 1) * chunkSize;
								if (Chunk* nextChunk = getChunk(nextPosition))
								{
									nextChunk->wakeUpChunk();
								}
							}
							if (j == cellVec[i].size() - 1 || j == cellVec[i].size() - 2)
							{
								sf::Vector2i nextPosition = chunkPosition;
								nextPosition.x = (nextPosition.x + 1) * chunkSize;;
								nextPosition.y = (nextPosition.y - 1) * chunkSize;
								if (Chunk* nextChunk = getChunk(nextPosition))
								{
									nextChunk->wakeUpChunk();
								}
							}
						}
						else if (i == cellVec.size() - 1 || i == cellVec.size() - 2)
						{
							sf::Vector2i nextPosition = chunkPosition;
							nextPosition.x *= chunkSize;
							nextPosition.y = (nextPosition.y + 1) * chunkSize;
							if (Chunk* nextChunk = getChunk(nextPosition))
							{
								nextChunk->wakeUpChunk();
							}
							if (j == 0 || j == 1)
							{
								sf::Vector2i nextPosition = chunkPosition;
								nextPosition.x = (nextPosition.x - 1) * chunkSize;;
								nextPosition.y = (nextPosition.y + 1) * chunkSize;
								if (Chunk* nextChunk = getChunk(nextPosition))
								{
									nextChunk->wakeUpChunk();
								}
							}
							if (j == cellVec[i].size() - 1 || j == cellVec[i].size() - 2)
							{
								sf::Vector2i nextPosition = chunkPosition;
								nextPosition.x = (nextPosition.x + 1) * chunkSize;;
								nextPosition.y = (nextPosition.y + 1) * chunkSize;
								if (Chunk* nextChunk = getChunk(nextPosition))
								{
									nextChunk->wakeUpChunk();
								}
							}
						}
						else if (j == 0 || j == 1)
						{
							sf::Vector2i nextPosition = chunkPosition;
							nextPosition.x = (nextPosition.x - 1) * chunkSize;;
							nextPosition.y = nextPosition.y * chunkSize;
							if (Chunk* nextChunk = getChunk(nextPosition))
							{
								nextChunk->wakeUpChunk();
							}
						}
						else if (j == cellVec[i].size() - 1 || j == cellVec[i].size() - 2)
						{
							sf::Vector2i nextPosition = chunkPosition;
							nextPosition.x = (nextPosition.x + 1) * chunkSize;;
							nextPosition.y = nextPosition.y * chunkSize;
							if (Chunk* nextChunk = getChunk(nextPosition))
							{
								nextChunk->wakeUpChunk();
							}
						}

					}
				}
			}
		}
		for (int i = 0; i < cellVec.size(); i++)
		{
			for (int j = 0; j < cellVec[i].size(); j++)
			{
				if (cellVec[i][j] != nullptr)
				{
					cellVec[i][j]->resetCell();
				}
			}
		}
		if (updated)
		{
			activeChunk = 2;
		}
		else
		{
			activeChunk--;
		}
	}
	return true;
}

void Chunk::updateImage(sf::Image& img, sf::Vector2f windowPosition, sf::Vector2f windowSize)
{
	sf::Vector2i startPosition = sf::Vector2i(chunkPosition.x * chunkSize - static_cast<int>(windowPosition.x), chunkPosition.y * chunkSize - static_cast<int>(windowPosition.y));
	sf::Vector2i endPosition = sf::Vector2i(chunkPosition.x * chunkSize + chunkSize - static_cast<int>(windowPosition.x),chunkPosition.y * chunkSize + chunkSize - static_cast<int>(windowPosition.y));
	if (startPosition.x < 0)
	{
		startPosition.x = 0;
	}
	if (startPosition.y < 0)
	{
		startPosition.y = 0;
	}
	if (endPosition.x > windowSize.x)
	{
		endPosition.x = static_cast<int>(windowSize.x);
	}
	if (endPosition.y > windowSize.y)
	{
		endPosition.y = static_cast<int>(windowSize.y);
	}
	for (int i = startPosition.y; i < endPosition.y; i++)
	{
		for (int j = startPosition.x; j < endPosition.x; j++)
		{
			Cell* cell = cellVec[i + int(windowPosition.y) - chunkPosition.y * chunkSize][j + int(windowPosition.x) - chunkPosition.x * chunkSize];
			if (cell)
			{
				img.setPixel(j, i, cell->getColour());
			}
		}
	}
}

bool Chunk::isVisible(sf::Vector2f windowPosition, sf::Vector2f windowSize)
{
	if (chunkPosition.x*chunkSize < windowPosition.x + windowSize.x && chunkPosition.x*chunkSize + chunkSize > windowPosition.x
		&& chunkPosition.y*chunkSize < windowPosition.y + windowSize.y && chunkPosition.y*chunkSize + chunkSize > windowPosition.y)
	{
		return true;
	}
	return false;
}

Chunk* Chunk::getChunk(sf::Vector2i chunkPosition)
{
	if (chunkPosition.x < 0 || chunkPosition.y < 0)
	{
		return nullptr;
	}
	auto coordinates = std::make_pair(chunkPosition.y / chunkSize, chunkPosition.x / chunkSize);
	auto it = chunkMap.find(coordinates);
	if (it != chunkMap.end())
	{
		return it->second;
	}
	else
	{
		if (coordinates.second > maxChunkX || coordinates.first > maxChunkY)
		{
			return nullptr;
		}
		auto newChunk = chunkMap.insert(std::pair<std::pair<int, int>, Chunk*>(coordinates, new Chunk(coordinates.second, coordinates.first, chunkMap)));
		return (*newChunk.first).second;
	}
}

void Chunk::spawnCell(CellTypes cellType, sf::Vector2i mousePosition)
{
	if (cellType == CellTypes::EMPTY )
	{
		if (cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize] != nullptr)
		{
			// Decrease number of cells
			cellNumber--;
		}
	}
	else
	{
		if (cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize] == nullptr)
		{
			// Increase number of cells
			cellNumber++;
		}
	}
	if (cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize])
	{
		delete cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize];
		cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize] = nullptr;
	}
	switch (cellType)
	{            
	case CellTypes::SAND:
		cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize] = new Sand();
		break;
	case CellTypes::STONE:
		cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize] = new Stone();
		break;
	case CellTypes::WATER:
		cellVec[mousePosition.y % chunkSize][mousePosition.x % chunkSize] = new Water();
		break;
	case CellTypes::GAS:
		break;
	case CellTypes::EMPTY:
		break;
	}
	// If chunk is inactive wake it up
	wakeUpChunk();
}
