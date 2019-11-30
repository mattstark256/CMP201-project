#include "AlgorithmTester.h"

#include "Map.h"
#include <algorithm> // std::sort
#include <iostream>
using namespace std;

// Clock stuff
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using the_clock = std::chrono::steady_clock;


AlgorithmTester::AlgorithmTester()
{
}


AlgorithmTester::~AlgorithmTester()
{
}


void AlgorithmTester::visualizeAlgorithm(Algorithm algorithm, int mapSize)
{
	cout << "Visualizing the ";
	printAlgorithmName(algorithm);
	cout << " algorithm with a map size of " << mapSize << ". Start and end points will be randomly selected.\n\n";

	// Generate map
	Map map(Vector2i(mapSize, mapSize));
	map.generateObstacles();

	// Generate start and end coords
	Vector2i start = pickEmptyCoord(map);
	Vector2i end = pickEmptyCoord(map, start);

	// Generate path
	Path path = getPathfinder(algorithm)->generateAndDrawPath(map, start, end, mapDisplayer);
}


void AlgorithmTester::testAlgorithm(Algorithm algorithm, int mapSize, int maps, int routes, int iterations)
{
	cout << "Testing the ";
	printAlgorithmName(algorithm);
	cout << " algorithm with a map size of " << mapSize << " over " << maps * routes * iterations << " iterations.\n\n";

	vector<float> times;

	for (int m = 0; m < maps; m++)
	{
		cout << "M";

		// Generate map
		Map map(Vector2i(mapSize, mapSize));
		map.generateObstacles();

		for (int r = 0; r < routes; r++)
		{
			cout << "R";

			// Generate start and end coords
			Vector2i start = pickEmptyCoord(map);
			Vector2i end = pickEmptyCoord(map, start);

			// Generate path
			the_clock::time_point startTime = the_clock::now();
			for (int i = 0; i < iterations; i++)
			{
				getPathfinder(algorithm)->generatePath(map, start, end);
			}
			the_clock::time_point endTime = the_clock::now();

			float time_taken = duration_cast<milliseconds>(endTime - startTime).count();
			time_taken /= iterations;
			times.push_back(time_taken);
		}
	}
	cout << "\n\n";

	sort(times.begin(), times.end());

	cout << "Median time is " << times[times.size() / 2] << "ms." << endl;

	//// Print all the times
	//for (int i = 0; i < times.size(); i++)
	//{
	//	cout << times[i] << "ms" << endl;
	//}
}


void AlgorithmTester::testAlgorithmsHeadToHead(Algorithm algorithm1, Algorithm algorithm2, int mapSize, int maps, int routes, int iterations)
{
	cout << "Testing the ";
	printAlgorithmName(algorithm1);
	cout << " algorithm against the ";
	printAlgorithmName(algorithm2);
	cout << " algorithm with a map size of " << mapSize << " over " << maps * routes * iterations << " iterations.\n\n";

	vector<float> times1;
	vector<float> times2;

	for (int m = 0; m < maps; m++)
	{
		cout << "M";

		// Generate map
		Map map(Vector2i(mapSize, mapSize));
		map.generateObstacles();

		for (int r = 0; r < routes; r++)
		{
			cout << "R";

			// Generate start and end coords
			Vector2i start = pickEmptyCoord(map);
			Vector2i end = pickEmptyCoord(map, start);

			// Generate path using first algorithm
			the_clock::time_point startTime1 = the_clock::now();
			for (int i = 0; i < iterations; i++)
			{
				getPathfinder(algorithm1)->generatePath(map, start, end);
			}
			the_clock::time_point endTime1 = the_clock::now();
			float time_taken1 = duration_cast<milliseconds>(endTime1 - startTime1).count();
			time_taken1 /= iterations;
			times1.push_back(time_taken1);

			// Generate path using second algorithm
			the_clock::time_point startTime2 = the_clock::now();
			for (int i = 0; i < iterations; i++)
			{
				getPathfinder(algorithm2)->generatePath(map, start, end);
			}
			the_clock::time_point endTime2 = the_clock::now();
			float time_taken2 = duration_cast<milliseconds>(endTime2 - startTime2).count();
			time_taken2 /= iterations;
			times2.push_back(time_taken2);
		}
	}
	cout << "\n\n";

	sort(times1.begin(), times1.end());
	sort(times2.begin(), times2.end());

	cout << "Median time for ";
	printAlgorithmName(algorithm1);
	cout << " algorithm: " << times1[times1.size() / 2] << "ms" << endl;
	cout << "Median time for ";
	printAlgorithmName(algorithm2);
	cout << " algorithm: " << times2[times2.size() / 2] << "ms" << endl;
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
	case AStarAlternate:
		return &alternateAStarPathfinder;
	default:
		break;
	}
}


void AlgorithmTester::printAlgorithmName(Algorithm algorithm)
{
	switch (algorithm)
	{
	case Lee:
		cout << "Lee";
		break;
	case Dijkstra:
		cout << "Dijkstra";
		break;
	case AStar:
		cout << "A*";
		break;
	case AStarAlternate:
		cout << "A* alternate";
		break;
	default:
		break;
	}
}


Vector2i AlgorithmTester::pickEmptyCoord(const Map & map)
{
	while (true)
	{
		Vector2i coord = Vector2i(rand() % map.getSize().x, rand() % map.getSize().y);
		if (map.getValue(coord) == 0) { return coord; }
	}
}


Vector2i AlgorithmTester::pickEmptyCoord(const Map & map, Vector2i invalidCoord)
{
	while (true)
	{
		Vector2i coord = Vector2i(rand() % map.getSize().x, rand() % map.getSize().y);
		if (map.getValue(coord) == 0 && coord != invalidCoord) { return coord; }
	}
}
