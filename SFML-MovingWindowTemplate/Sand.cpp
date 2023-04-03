#include "Sand.h"

bool Sand::update(sf::Vector2i position, Chunk* chunk)
{
	updated = true;

	if (MoveableSolid::update(position, chunk))
	{
		return true;
	}
	else
	{
		if (position.y + 1 < chunk->getSize() && position.x + 1 < chunk->getSize())
		{
			if (!chunk->cellVec[position.y + 1][position.x + 1])
			{
				chunk->cellVec[position.y + 1][position.x + 1] = this;
				chunk->cellVec[position.y][position.x] = nullptr;
				return true;
			}
			else
			{
			}
		}
		else
		{
			sf::Vector2i chunkPosition = chunk->getChunkPosition();
			if (position.y + 1 >= chunk->getSize())
			{
				chunkPosition.y = (chunkPosition.y + 1) * chunk->getSize();
			}
			else
			{
				chunkPosition.y *= chunk->getSize();
			}
			if (position.x + 1 >= chunk->getSize())
			{
				chunkPosition.x = (chunkPosition.x + 1) * chunk->getSize();
			}
			else
			{
				chunkPosition.x *= chunk->getSize();
			}
			Chunk* nextChunk = chunk->getChunk(chunkPosition);
			if (nextChunk)
			{
				if (!nextChunk->cellVec[(position.y + 1) % chunk->getSize()][(position.x + 1) % chunk->getSize()])
				{
					nextChunk->cellVec[(position.y + 1) % chunk->getSize()][(position.x + 1) % chunk->getSize()] = this;
					nextChunk->increaseCellNumber();
					nextChunk->wakeUpChunk();
					chunk->cellVec[position.y][position.x] = nullptr;
					chunk->decreaseCellNumber();
					return true;
				}
				else
				{

				}
			}
		}
		if (position.y + 1 < chunk->getSize() && position.x - 1 >= 0)
		{
			if (!chunk->cellVec[position.y + 1][position.x - 1])
			{
				chunk->cellVec[position.y + 1][position.x - 1] = this;
				chunk->cellVec[position.y][position.x] = nullptr;
				return true;
			}
			else
			{
			}
		}
		else
		{
			sf::Vector2i chunkPosition = chunk->getChunkPosition();
			if (position.y + 1 >= chunk->getSize())
			{
				chunkPosition.y = (chunkPosition.y + 1) * chunk->getSize();
			}
			else
			{
				chunkPosition.y *= chunk->getSize();
			}
			if (position.x - 1 < 0)
			{
				chunkPosition.x = (chunkPosition.x - 1) * chunk->getSize();
			}
			else
			{
				chunkPosition.x *= chunk->getSize();
			}
			Chunk* nextChunk = chunk->getChunk(chunkPosition);
			if (nextChunk)
			{
				if (!nextChunk->cellVec[(position.y + 1) % chunk->getSize()][(position.x + chunk->getSize() - 1) % chunk->getSize()])
				{
					nextChunk->cellVec[(position.y + 1) % chunk->getSize()][(position.x + chunk->getSize() - 1) % chunk->getSize()] = this;
					nextChunk->increaseCellNumber();
					nextChunk->wakeUpChunk();
					chunk->cellVec[position.y][position.x] = nullptr;
					chunk->decreaseCellNumber();
					return true;
				}
				else
				{

				}
			}
		}
	}
	return false;
}
