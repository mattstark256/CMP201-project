#pragma once

#include "MapDisplayer.h"
#include "LeePathfinder.h"
#include "AStarPathfinder.h"
#include "AlternateAStarPathfinder.h"

enum Algorithm { Lee, Dijkstra, AStar, AStarAlternate };


class AlgorithmTester
{
public:
	AlgorithmTester();
	~AlgorithmTester();

	void visualizeAlgorithm(Algorithm algorithm, int mapSize);

	void testAlgorithm(Algorithm algorithm, int mapSize, int maps, int routes, int iterations);
	void testAlgorithmsHeadToHead(Algorithm algorithm1, Algorithm algorithm2, int mapSize, int maps, int routes, int iterations);

private:
	MapDisplayer mapDisplayer;
	LeePathfinder leePathfinder;
	AStarPathfinder aStarPathfinder;
	AlternateAStarPathfinder alternateAStarPathfinder;

	Pathfinder* getPathfinder(Algorithm algorithm);
	void printAlgorithmName(Algorithm algorithm);
	Vector2i pickEmptyCoord(const Map& map);
	Vector2i pickEmptyCoord(const Map& map, Vector2i invalidCoord);
};

