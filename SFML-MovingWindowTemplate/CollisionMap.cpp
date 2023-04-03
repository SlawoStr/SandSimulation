#include "CollisionMap.h"

void CollisionMap::addEntry(const std::string& cellType1, const std::string& cellType2, HitFunctionPtr collisionFunction)
{
	hitMap[std::make_pair(cellType1, cellType2)] = collisionFunction;
}

void CollisionMap::removeEntry(const std::string& cellType1, const std::string& cellType2)
{
	hitMap.erase(std::make_pair(cellType1, cellType2));
}

CollisionMap::HitFunctionPtr CollisionMap::lookUp(const std::string& cellType1, const std::string& cellType2)
{
	auto mapEntry = hitMap.find(std::make_pair(cellType1, cellType2));
	// Collision was found in map
	if (mapEntry != hitMap.end())
	{
		return (*mapEntry).second;
	}
	return nullptr;
}

CollisionMap& CollisionMap::theCollisionMap()
{
	static CollisionMap collisionMap;
	return collisionMap;
}