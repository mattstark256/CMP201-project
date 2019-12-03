#include "AlgorithmTester.h"

#include "Map.h"
#include <algorithm> // std::sort
#include <iostream>
#include <fstream>
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
	cout << "Visualizing the " << getAlgorithmName(algorithm) << " algorithm with a map size of " << mapSize << ". Start and end points will be randomly selected.\n\n";

	// Generate map
	Map map(Vector2i(mapSize, mapSize));
	map.generateObstacles();

	// Generate start and end coords
	Vector2i start = pickEmptyCoord(map);
	Vector2i end = pickEmptyCoord(map, start);

	// Generate path
	Path path = getPathfinder(algorithm)->generatePath(map, start, end, &mapDisplayer);

	ofstream my_file("Test Results/hello.csv");
	my_file << "Hello, world!\n";
	my_file << "Goodbye, world!\n";
}


void AlgorithmTester::testAlgorithm(Algorithm algorithm, int mapSize, int maps, int routes, int iterations)
{
	cout << "Testing the " << getAlgorithmName(algorithm) << " algorithm with a map size of " << mapSize << " over " << maps * routes * iterations << " iterations.\n\n";

	vector<float> times;

	for (int m = 0; m < maps; m++)
	{
		cout << "Map " << m + 1 << ", Size " << mapSize << "x" << mapSize << ", Testing " << routes << " routes";

		// Generate map
		Map map(Vector2i(mapSize, mapSize));
		map.generateObstacles();

		for (int r = 0; r < routes; r++)
		{
			cout << ".";

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

			// Get the average time taken for this specific path. This reduces ms rounding error.
			float time_taken = duration_cast<milliseconds>(endTime - startTime).count();
			time_taken /= iterations;
			times.push_back(time_taken);
		}
		cout << endl;
	}
	cout << endl;

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
	cout << "Testing the " << getAlgorithmName(algorithm1) << " algorithm against the " << getAlgorithmName(algorithm2);
	cout << " algorithm with a map size of " << mapSize << " over " << maps * routes * iterations << " iterations.\n\n";

	vector<float> times1;
	vector<float> times2;
	int wins1 = 0;
	int wins2 = 0;

	for (int m = 0; m < maps; m++)
	{
		cout << "Map " << m + 1 << ", Size " << mapSize << "x" << mapSize << ", Testing " << routes << " routes";

		// Generate map
		Map map(Vector2i(mapSize, mapSize));
		map.generateObstacles();

		for (int r = 0; r < routes; r++)
		{
			cout << ".";

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

			if (time_taken1 < time_taken2) wins1++;
			else if (time_taken2 < time_taken1) wins2++;
		}
		cout << endl;
	}
	cout << endl;

	sort(times1.begin(), times1.end());
	sort(times2.begin(), times2.end());

	int numberOfTests = maps * routes;

	cout << "Median time for " << getAlgorithmName(algorithm1) << " algorithm: " << times1[times1.size() / 2] << "ms" << endl;
	cout << "It was faster in " << wins1 << " out of " << numberOfTests << " tests." << endl;
	cout << "Median time for " << getAlgorithmName(algorithm2) << " algorithm: " << times2[times2.size() / 2] << "ms" << endl;
	cout << "It was faster in " << wins2 << " out of " << numberOfTests << " tests." << endl;
}


void AlgorithmTester::testAlgorithmPerformanceVsMapSize(Algorithm algorithm, int numberOfMapSizes, int firstMapSize, int mapSizeInterval, int mapsPerSize, int routes, int iterations)
{
	// Create an array of vectors of times. Each vector represents one map size.
	vector<float>* times = new vector<float>[numberOfMapSizes] {};

	for (int m = 0; m < mapsPerSize; m++)
	{
		for (int s = 0; s < numberOfMapSizes; s++)
		{
			int mapSize = firstMapSize + s * mapSizeInterval;
			cout << "Map " << m * numberOfMapSizes + s + 1 << ", Size " << mapSize << "x" << mapSize << ", Testing " << routes << " routes";

			// Generate map
			Map map(Vector2i(mapSize, mapSize));
			map.generateObstacles();

			for (int r = 0; r < routes; r++)
			{
				cout << ".";

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

				// Get the average time taken for this specific path. This reduces ms rounding error.
				float time_taken = duration_cast<milliseconds>(endTime - startTime).count();
				time_taken /= iterations;
				times[s].push_back(time_taken);
			}
			cout << endl;
		}
	}
	cout << endl;

	// Create file
	string filePath = "Test Results/" + getAlgorithmName(algorithm) + ".csv";
	ofstream my_file(filePath);
	cout << "Writing results to " << filePath << endl;

	// Write to file
	my_file << "Time to find Shortest Path vs. Map Size" << endl;
	my_file << "Map Size, " << getAlgorithmName(algorithm) << endl;
	for (int s = 0; s < numberOfMapSizes; s++)
	{
		int mapSize = firstMapSize + s * mapSizeInterval;
		sort(times[s].begin(), times[s].end());
		float median = times[s][times[s].size() / 2];
		my_file << mapSize << ", " << median << endl;
	}

	delete[] times;
}


void AlgorithmTester::testAlgorithmsHeadToHeadPerformanceVsMapSize(Algorithm algorithm1, Algorithm algorithm2, int numberOfMapSizes, int firstMapSize, int mapSizeInterval, int mapsPerSize, int routes, int iterations)
{
	// Create an array of vectors of times. Each vector represents one map size.
	vector<float>* times1 = new vector<float>[numberOfMapSizes] {};
	vector<float>* times2 = new vector<float>[numberOfMapSizes] {};

	int* wins1 = new int[numberOfMapSizes] {};
	int* wins2 = new int[numberOfMapSizes] {};

	for (int m = 0; m < mapsPerSize; m++)
	{
		for (int s = 0; s < numberOfMapSizes; s++)
		{
			int mapSize = firstMapSize + s * mapSizeInterval;
			cout << "Map " << m * numberOfMapSizes + s + 1 << ", Size " << mapSize << "x" << mapSize << ", Testing " << routes << " routes";

			// Generate map
			Map map(Vector2i(mapSize, mapSize));
			map.generateObstacles();

			for (int r = 0; r < routes; r++)
			{
				cout << ".";

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
				times1[s].push_back(time_taken1);

				// Generate path using second algorithm
				the_clock::time_point startTime2 = the_clock::now();
				for (int i = 0; i < iterations; i++)
				{
					getPathfinder(algorithm2)->generatePath(map, start, end);
				}
				the_clock::time_point endTime2 = the_clock::now();
				float time_taken2 = duration_cast<milliseconds>(endTime2 - startTime2).count();
				time_taken2 /= iterations;
				times2[s].push_back(time_taken2);

				if (time_taken1 < time_taken2) wins1[s]++;
				else if (time_taken2 < time_taken1) wins2[s]++;
			}
			cout << endl;
		}
	}
	cout << endl;

	// Create file
	string filePath = "Test Results/" + getAlgorithmName(algorithm1) + " vs " + getAlgorithmName(algorithm2) + ".csv";
	ofstream my_file(filePath);
	cout << "Writing results to " << filePath << endl;

	// Write median times to file
	my_file << "Median Time to find Shortest Path vs. Map Size" << endl;
	my_file << "Map Size, " << getAlgorithmName(algorithm1) << ", " << getAlgorithmName(algorithm2) << endl;
	for (int s = 0, mapSize = firstMapSize; s < numberOfMapSizes; s++, mapSize += mapSizeInterval)
	{
		sort(times1[s].begin(), times1[s].end());
		float median1 = times1[s][times1[s].size() / 2];
		sort(times2[s].begin(), times2[s].end());
		float median2 = times2[s][times2[s].size() / 2];
		my_file << mapSize << ", " << median1 << ", " << median2 << endl;
	}

	// Write win percentages to file
	my_file << "Percentage of Wins vs. Map Size" << endl;
	my_file << "Map Size, " << getAlgorithmName(algorithm1) << ", " << getAlgorithmName(algorithm2) << endl;
	for (int s = 0, mapSize = firstMapSize; s < numberOfMapSizes; s++, mapSize+= mapSizeInterval)
	{
		int testsPerSize = mapsPerSize * routes;
		float win1 = (float)wins1[s] / testsPerSize * 100;
		float win2 = (float)wins2[s] / testsPerSize * 100;
		my_file << mapSize << ", " << win1 << ", " << win2 << endl;
	}

	delete[] times1;
	delete[] times2;
}


Pathfinder* AlgorithmTester::getPathfinder(Algorithm algorithm)
{
	switch (algorithm)
	{
	case Lee:
		return &leePathfinder;
	case Dijkstra:
		return &dijkstraPathfinder;
	case AStar:
		return &aStarPathfinder;
	case AStarAlternate:
		return &alternateAStarPathfinder;
	default:
		break;
	}
}


string AlgorithmTester::getAlgorithmName(Algorithm algorithm)
{
	switch (algorithm)
	{
	case Lee:
		return "Lee";
	case Dijkstra:
		return "Dijkstra";
	case AStar:
		return "A Star";
	case AStarAlternate:
		return "A Star Alternate";
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
