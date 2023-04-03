#include "Water.h"

bool Water::update(sf::Vector2i position, Chunk* chunk)
{
	updated = true;

	if (Liquid::update(position, chunk))
	{
		return true;
	}
	return false;
}
