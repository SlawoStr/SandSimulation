#include "ChunkManager.h"

ChunkManager::ChunkManager()
{
	//gameMap.insert(std::pair<std::pair<int, int>, Chunk*>(std::make_pair(0, 0), new Chunk(0, 0, gameMap)));
}

void ChunkManager::update(sf::Image& image,sf::Vector2f windowPosition, sf::Vector2f windowSize)
{
	for (auto it = gameMap.begin(); it != gameMap.end();)
	{
		if (!(*it).second->update())
		{
			gameMap.erase(it++);
		}
		else
		{
			++it;
		}
	}
	std::for_each(gameMap.begin(), gameMap.end(), [&](auto& pair)
		{
			if (pair.second->isVisible(windowPosition, windowSize))
				pair.second->updateImage(image, windowPosition, windowSize);
		});
}

void ChunkManager::spawnCell(CellTypes cellType, sf::Vector2f mousePosition)
{
	if (mousePosition.x < 0 || mousePosition.y < 0)
	{
		return;
	}
	sf::Vector2i mousePos(int(mousePosition.x), int(mousePosition.y));
	auto coordinates = std::make_pair(mousePos.y / Chunk::getSize(), mousePos.x / Chunk::getSize());
	auto it = gameMap.find(coordinates);
	if (it != gameMap.end())
	{
		(*it).second->spawnCell(cellType, mousePos);
	}
	else
	{
		if (coordinates.second > Chunk::getMaxX() || coordinates.first > Chunk::getMaxY())
		{
			return;
		}
		auto newChunk = gameMap.insert(std::pair<std::pair<int, int>, Chunk*>(coordinates, new Chunk(coordinates.second, coordinates.first, gameMap)));
		(*newChunk.first).second->spawnCell(cellType, mousePos);
	}
}

void ChunkManager::draw(sf::RenderTarget& target)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(static_cast<float>(Chunk::getSize()),static_cast<float>(Chunk::getSize())));
	for (const auto & it : gameMap)
	{
		if (it.second->isActive())
		{
			shape.setFillColor(sf::Color(0, 50, 152, 100));
		}
		else
		{
			shape.setFillColor(sf::Color(152, 255, 152, 100));
		}
		shape.setPosition(static_cast<float>(it.first.second * Chunk::getSize()), static_cast<float>(it.first.first * Chunk::getSize()));
		target.draw(shape);
	}
}

