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


void AlgorithmTester::benchmarkAlgorithms(std::vector<Algorithm> algorithms, int mapSizes, int firstMapSize, int mapSizeInterval, int mapsPerSize, int routesPerMap, int testsPerRoute)
{
	int numberOfAlgorithms = algorithms.size();

	// Create a array of arrays of vectors of floats.
	// First array is for each algorithm, second is for each map size and the vector is for each measured time.
	vector<float>** times = new vector<float>*[numberOfAlgorithms] {};
	for (int i = 0; i < numberOfAlgorithms; i++)
	{
		times[i] = new vector<float>[mapSizes] {};
	}

	// Create a array of arrays of ints
	// First array is for each algorithm, second is for each map size.
	int** wins = new int*[numberOfAlgorithms] {};
	for (int i = 0; i < numberOfAlgorithms; i++)
	{
		wins[i] = new int[mapSizes] {};
	}


	for (int m = 0; m < mapsPerSize; m++)
	{
		for (int s = 0; s < mapSizes; s++)
		{
			int mapSize = firstMapSize + s * mapSizeInterval;
			cout << "Map " << m * mapSizes + s + 1 << ", Size " << mapSize << "x" << mapSize << ", Testing " << routesPerMap << " routes";

			// Generate map
			Map map(Vector2i(mapSize, mapSize));
			map.generateObstacles();

			for (int r = 0; r < routesPerMap; r++)
			{
				cout << ".";

				// Generate start and end coords
				Vector2i start = pickEmptyCoord(map);
				Vector2i end = pickEmptyCoord(map, start);

				int fastestAlgorithm;
				float shortestTime;
				bool isDraw;

				for (int a = 0; a < numberOfAlgorithms; a++)
				{
					the_clock::time_point startTime = the_clock::now();
					for (int t = 0; t < testsPerRoute; t++)
					{
						getPathfinder(algorithms[a])->generatePath(map, start, end);
					}
					the_clock::time_point endTime = the_clock::now();
					float time_taken = duration_cast<milliseconds>(endTime - startTime).count();
					time_taken /= testsPerRoute;
					times[a][s].push_back(time_taken);

					// If it's the fastest so far
					if (a == 0 || time_taken < shortestTime)
					{
						fastestAlgorithm = a;
						shortestTime = time_taken;
						isDraw = false;
					}
					// If it's as fast as the current fastest
					else if (time_taken == shortestTime)
					{
						isDraw = true;
					}
				}

				// If one algorithm was fastest
				if (!isDraw)
				{
					wins[fastestAlgorithm][s]++;
				}
			}
			cout << endl;
		}
	}
	cout << endl;


	// Create file
	string filePath = "Test Results/";
	for (int a = 0; a < numberOfAlgorithms; a++)
	{
		if (a > 0) filePath += " vs ";
		filePath += getAlgorithmName(algorithms[a]);
	}
	filePath += ".csv";
	ofstream my_file(filePath);
	cout << "Writing results to " << filePath << endl;

	// Write details of test to file
	my_file << "Map sizes, " << mapSizes << endl;
	my_file << "Maps per size, " << mapsPerSize << endl;
	my_file << "Routes per map, " << routesPerMap << endl;
	int routesPerMapSize = mapsPerSize * routesPerMap;
	my_file << "Routes per map size, " << routesPerMapSize << endl;
	my_file << "Tests per route, " << testsPerRoute << endl;

	// Write median times to file
	my_file << endl;
	my_file << "Median Time to find Shortest Path vs. Map Size" << endl;
	my_file << "Map Size";
	for (int a = 0; a < numberOfAlgorithms; a++){ my_file << ", " << getAlgorithmName(algorithms[a]); }
	my_file << endl;
	for (int s = 0, mapSize = firstMapSize; s < mapSizes; s++, mapSize += mapSizeInterval)
	{
		my_file << mapSize;
		for (int a = 0; a < numberOfAlgorithms; a++)
		{
			sort(times[a][s].begin(), times[a][s].end());
			float medianTime = times[a][s][routesPerMapSize / 2];
			my_file << ", " << medianTime;
		}
		my_file << endl;
	}

	// If there was only one algorithm, it will have always been the fastest so it's not worth writing its win count
	if (numberOfAlgorithms > 1)
	{
		// Write win percentages to file
		my_file << endl;
		my_file << "Percentage of Wins vs. Map Size" << endl;
		my_file << "Map Size";
		for (int a = 0; a < numberOfAlgorithms; a++) { my_file << ", " << getAlgorithmName(algorithms[a]); }
		my_file << endl;
		for (int s = 0, mapSize = firstMapSize; s < mapSizes; s++, mapSize += mapSizeInterval)
		{
			my_file << mapSize;
			for (int a = 0; a < numberOfAlgorithms; a++)
			{
				float winPercent = (float)wins[a][s] / routesPerMapSize * 100;
				my_file << ", " << winPercent;
			}
			my_file << endl;
		}
	}

	// Write all times to file
	my_file << endl;
	my_file << "Time to find Shortest Path vs. Map Size" << endl;
	my_file << "Map Size" << endl;
	for (int s = 0, mapSize = firstMapSize; s < mapSizes; s++, mapSize += mapSizeInterval)
	{
		if (s > 0) my_file << ", ";
		my_file << mapSize;
	}
	my_file << endl;
	for (int a = 0; a < numberOfAlgorithms; a++)
	{
		my_file << getAlgorithmName(algorithms[a]) << endl;
		for (int i = 0; i < routesPerMapSize; i++)
		{
			for (int s = 0; s < mapSizes; s++)
			{
				if (s > 0) my_file << ", ";
				my_file << times[a][s][i];
			}
			my_file << endl;
		}
	}


	// Delete times
	for (int i = 0; i < numberOfAlgorithms; i++)
	{
		delete[] times[i];
	}
	delete[] times;

	// Delete wins
	for (int i = 0; i < numberOfAlgorithms; i++)
	{
		delete[] wins[i];
	}
	delete[] wins;
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
