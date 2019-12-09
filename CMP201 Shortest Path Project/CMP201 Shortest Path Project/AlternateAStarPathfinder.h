#pragma once
#include "Pathfinder.h"

#include "AStarNode.h"
#include "AlternateAStarOpenSet.h"
#include "AlternateAStarClosedSet.h"

#define MOVEMENT_DIRECTIONS 8


// Pathfinder using the A* algorithm
// This is a copy of AStarPathfinder. I can change specific parts and benchmark them against each other to see if the change improves performance.


class AlternateAStarPathfinder :
	public Pathfinder
{
public:
	AlternateAStarPathfinder();
	~AlternateAStarPathfinder();

	Path generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer = nullptr) override;

private:
	AlternateAStarOpenSet openSet;
	AlternateAStarClosedSet closedSet;

	float findHeuristic(Vector2i a, Vector2i b);

	int xOffsets[MOVEMENT_DIRECTIONS]{ 1, 1, 0, -1, -1, -1, 0, 1 };
	int yOffsets[MOVEMENT_DIRECTIONS]{ 0, 1, 1, 1, 0, -1, -1, -1 };
	float distances[MOVEMENT_DIRECTIONS]{ 1, 1.414, 1, 1.414, 1, 1.414, 1, 1.414 };
	bool isDiagonal[MOVEMENT_DIRECTIONS]{ false, true, false, true, false, true, false, true };
};

