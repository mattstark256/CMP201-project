#pragma once
#include "Pathfinder.h"

#include "AStarNode.h"
#include "AStarOpenList.h"
#include "AStarClosedList.h"

#define MOVEMENT_DIRECTIONS 8


class AStarPathfinder :
	public Pathfinder
{
public:
	AStarPathfinder();
	~AStarPathfinder();

	Path generatePath(const Map& map, Vector2i start, Vector2i end) override;

private:
	AStarOpenList openList;
	AStarClosedList closedList;

	float getHeuristic(Vector2i a, Vector2i b);

	int xOffsets[MOVEMENT_DIRECTIONS]{ 1, 1, 0, -1, -1, -1, 0, 1 };
	int yOffsets[MOVEMENT_DIRECTIONS]{ 0, 1, 1, 1, 0, -1, -1, -1 };
	float distances[MOVEMENT_DIRECTIONS]{ 1, 1.414, 1, 1.414, 1, 1.414, 1, 1.414 };
	bool isDiagonal[MOVEMENT_DIRECTIONS]{ false, true, false, true, false, true, false, true };
};

