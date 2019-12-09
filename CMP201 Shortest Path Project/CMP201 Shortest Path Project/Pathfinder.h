#pragma once

#include "Path.h"
#include "Map.h"
#include "MapDisplayer.h"


// This is the base class from which the pathfinding algorithms inherit


class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	virtual Path generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer = nullptr);
};

