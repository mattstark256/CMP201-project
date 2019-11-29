#include "AlgorithmTester.h"

#include "Map.h"


AlgorithmTester::AlgorithmTester()
{
}


AlgorithmTester::~AlgorithmTester()
{
}


void AlgorithmTester::visualizeAlgorithm(Algorithm algorithm, int mapSize)
{
	Map map(Vector2i(mapSize, mapSize));
	map.generateObstacles();

	// Generate start and end coords
	Vector2i start, end;
	while (true)
	{
		start = Vector2i(rand() % map.getSize().x, rand() % map.getSize().y);
		if (map.getValue(start) == 0) break;
	}
	while (true)
	{
		end = Vector2i(rand() % map.getSize().x, rand() % map.getSize().y);
		if (map.getValue(end) == 0 && end != start) break;
	}

	// Generate path
	Path path = getPathfinder(algorithm)->generatePath(map, start, end, true, &mapDisplayer);
}


Pathfinder* AlgorithmTester::getPathfinder(Algorithm algorithm)
{
	switch (algorithm)
	{
	case Lee:
		break;
	case Dijkstra:
		break;
	case AStar:
		return &aStarPathfinder;
	default:
		break;
	}
}
