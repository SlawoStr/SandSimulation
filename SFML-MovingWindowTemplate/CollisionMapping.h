#pragma once
#include "Gas.h"
#include "Poison.h"
#include "Water.h"
#include "Sand.h"
#include "Stone.h"


void StoneWaterCollision(Cell& stoneCell, Cell& waterCell, Chunk* firstChunk, Chunk* secondChunk)
{
}


void registerCollision()
{
	CollisionMap::theCollisionMap().addEntry("Stone", "Water", &StoneWaterCollision);
}