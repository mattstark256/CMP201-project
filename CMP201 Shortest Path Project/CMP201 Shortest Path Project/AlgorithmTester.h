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
	void benchmarkAlgorithms(std::vector<Algorithm> algorithms, int mapSizes, int firstMapSize, int mapSizeInterval, int mapsPerSize, int journeysPerMap);

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

