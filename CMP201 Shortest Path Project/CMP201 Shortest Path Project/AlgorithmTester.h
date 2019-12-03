#pragma once

#include "MapDisplayer.h"
#include "LeePathfinder.h"
#include "DijkstraPathfinder.h"
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
	void testAlgorithmPerformanceVsMapSize(Algorithm algorithm, int numberOfMapSizes, int firstMapSize, int mapSizeInterval, int mapsPerSize, int routes, int iterations);
	void testAlgorithmsHeadToHeadPerformanceVsMapSize(Algorithm algorithm1, Algorithm algorithm2, int numberOfMapSizes, int firstMapSize, int mapSizeInterval, int mapsPerSize, int routes, int iterations);

private:
	MapDisplayer mapDisplayer;
	LeePathfinder leePathfinder;
	DijkstraPathfinder dijkstraPathfinder;
	AStarPathfinder aStarPathfinder;
	AlternateAStarPathfinder alternateAStarPathfinder;

	Pathfinder* getPathfinder(Algorithm algorithm);
	std::string getAlgorithmName(Algorithm algorithm);
	Vector2i pickEmptyCoord(const Map& map);
	Vector2i pickEmptyCoord(const Map& map, Vector2i invalidCoord);
};

