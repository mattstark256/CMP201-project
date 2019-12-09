#pragma once
#include "Pathfinder.h"

#define MOVEMENT_DIRECTIONS 4


// Pathfinder using the Lee algorithm


class LeePathfinder :
	public Pathfinder
{
public:
	LeePathfinder();
	~LeePathfinder();

	Path generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer = nullptr) override;

private:
	int xOffsets[MOVEMENT_DIRECTIONS]{ 1, 0, -1, 0 };
	int yOffsets[MOVEMENT_DIRECTIONS]{ 0, 1, 0, -1 };
};

