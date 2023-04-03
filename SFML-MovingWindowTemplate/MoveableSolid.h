#pragma once
#include "Solid.h"
#include <iostream>
#include "Chunk.h"

class MoveableSolid : public Solid
{
protected:
	bool update(sf::Vector2i position, Chunk* chunk)
	{
		if (position.y + 1 < chunk->getSize())
		{
			if (!chunk->cellVec[position.y + 1][position.x])
			{
				chunk->cellVec[position.y + 1][position.x] = this;
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
			chunkPosition.x *= chunk->getSize();
			chunkPosition.y = (chunkPosition.y + 1) * chunk->getSize();
			Chunk* nextChunk = chunk->getChunk(chunkPosition);
			if (!nextChunk)
			{
				return false;
			}
			if (!nextChunk->cellVec[0][position.x])
			{
				nextChunk->cellVec[position.y + 1 - chunk->getSize()][position.x] = this;
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
		return false;
	}
};