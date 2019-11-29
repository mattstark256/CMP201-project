#pragma once

#include "MapDisplayer.h"
#include "AStarPathfinder.h"

enum Algorithm { Lee, Dijkstra, AStar };


class AlgorithmTester
{
public:
	AlgorithmTester();
	~AlgorithmTester();

	void visualizeAlgorithm(Algorithm algorithm, int mapSize);

private:
	MapDisplayer mapDisplayer;
	AStarPathfinder aStarPathfinder;

	Pathfinder* getPathfinder(Algorithm algorithm);
};

