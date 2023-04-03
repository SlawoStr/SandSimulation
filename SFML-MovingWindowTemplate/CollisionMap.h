#pragma once
#include <string>
#include <map>
#include "Cell.h"

class Cell;
class Chunk;

class CollisionMap
{
	using HitFunctionPtr = void(*)(Cell& lhs, Cell& rhs,Chunk* fhs,Chunk* shs);
	using HitMap = std::map<std::pair<std::string, std::string>, HitFunctionPtr>;
public:
	// Add new collision to map
	void addEntry(const std::string& cellType1, const std::string& cellType2, HitFunctionPtr collisionFunction);
	// Remove existing collision from map
	void removeEntry(const std::string& cellType1, const std::string& cellType2);
	// Get pointer to a function that will handle this type of collision
	HitFunctionPtr lookUp(const std::string& cellType1, const std::string& cellType2);
	// Singelton acess
	static CollisionMap& theCollisionMap();
private:
	HitMap hitMap;
	// Hit Map can be created only once
	CollisionMap() {};
	CollisionMap(const CollisionMap&) = delete;
};