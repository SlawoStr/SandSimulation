#include "Stone.h"

bool Stone::update(sf::Vector2i position, Chunk* chunk)
{
	updated = true;

	if (MoveableSolid::update(position, chunk))
	{
		return true;
	}
	return false;
}
