#pragma once
#include "Pathfinder.h"

#include "AStarNode.h"
#include "AlternateAStarOpenSet.h"
#include "AlternateAStarClosedSet.h"

#define MOVEMENT_DIRECTIONS 8


class AlternateAStarPathfinder :
	public Pathfinder
{
public:
	AlternateAStarPathfinder();
	~AlternateAStarPathfinder();

	Path generatePath(const Map& map, Vector2i start, Vector2i end) override;
	Path generateAndDrawPath(const Map& map, Vector2i start, Vector2i end, MapDisplayer& mapDisplayer) override;

private:
	AlternateAStarOpenSet openSet;
	AlternateAStarClosedSet closedSet;
	bool deleteSets = true;

	float findHeuristic(Vector2i a, Vector2i b);

	int xOffsets[MOVEMENT_DIRECTIONS]{ 1, 1, 0, -1, -1, -1, 0, 1 };
	int yOffsets[MOVEMENT_DIRECTIONS]{ 0, 1, 1, 1, 0, -1, -1, -1 };
	float distances[MOVEMENT_DIRECTIONS]{ 1, 1.414, 1, 1.414, 1, 1.414, 1, 1.414 };
	bool isDiagonal[MOVEMENT_DIRECTIONS]{ false, true, false, true, false, true, false, true };
};

