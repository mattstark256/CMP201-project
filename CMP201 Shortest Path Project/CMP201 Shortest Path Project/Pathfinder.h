#pragma once

#include "Path.h"
#include "Map.h"
#include "MapDisplayer.h"


class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	virtual Path generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer = nullptr);
};

