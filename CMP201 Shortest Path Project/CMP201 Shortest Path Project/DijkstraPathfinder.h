#pragma once
#include "Pathfinder.h"

#include "DijkstraNode.h"
#include "DijkstraOpenSet.h"
#include "DijkstraClosedSet.h"

#define MOVEMENT_DIRECTIONS 8


// Pathfinder using the Dijkstra algorithm


class DijkstraPathfinder :
	public Pathfinder
{
public:
	DijkstraPathfinder();
	~DijkstraPathfinder();

	Path generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer = nullptr) override;

private:
	DijkstraOpenSet openSet;
	DijkstraClosedSet closedSet;

	int xOffsets[MOVEMENT_DIRECTIONS]{ 1, 1, 0, -1, -1, -1, 0, 1 };
	int yOffsets[MOVEMENT_DIRECTIONS]{ 0, 1, 1, 1, 0, -1, -1, -1 };
	float distances[MOVEMENT_DIRECTIONS]{ 1, 1.414, 1, 1.414, 1, 1.414, 1, 1.414 };
	bool isDiagonal[MOVEMENT_DIRECTIONS]{ false, true, false, true, false, true, false, true };
};