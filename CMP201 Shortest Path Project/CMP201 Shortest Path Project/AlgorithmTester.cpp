#include "AlgorithmTester.h"

#include "Map.h"
#include <algorithm> // sort
#include <iostream>
#include <fstream> // ofstream, used for writing to CSV file
using namespace std;

// Set up clock
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using the_clock = std::chrono::steady_clock;


AlgorithmTester::AlgorithmTester()
{
}


AlgorithmTester::~AlgorithmTester()
{
}


// Find a path using the specified algorithm then display the results
void AlgorithmTester::visualizeAlgorithm(Algorithm algorithm, int mapSize)
{
	cout << "Visualizing the " << getAlgorithmName(algorithm) << " algorithm with a map size of " << mapSize << ". Start and end points will be randomly selected.\n\n";

	// Generate map
	Map map(Vector2i(mapSize, mapSize));
	map.generateObstacles();

	// Generate start and end coords
	Vector2i start = pickEmptyCoord(map);
	Vector2i end = pickEmptyCoord(map, start);

	// Generate path and display it
	Path path = getPathfinder(algorithm)->generatePath(map, start, end, &mapDisplayer);
}


// Benchmark the specified algorithms then save the results to a CSV file.
void AlgorithmTester::benchmarkAlgorithms(
	std::vector<Algorithm> algorithms,		// The algorithms to be benchmarked
	int mapSizes,							// The number of different map sizes to test
	int firstMapSize,						// The first map size
	int mapSizeInterval,					// The difference between consecutive map sizes
	int mapsPerSize,						// The number of random maps to be generated for each map size
	int journeysPerMap)						// The number of random journeys to be tested for each map
{
	int numberOfAlgorithms = algorithms.size();

	// Create a array of arrays of vectors of floats representing times to find paths.
	// First array is for each algorithm, second is for each map size and the vector is for each journey.
	vector<float>** times = new vector<float>*[numberOfAlgorithms] {};
	for (int i = 0; i < numberOfAlgorithms; i++)
	{
		times[i] = new vector<float>[mapSizes] {};
	}

	// Create a array of arrays of ints representing number of times each algorithm is faster than the others
	// First array is for each algorithm, second is for each map size.
	int** wins = new int*[numberOfAlgorithms] {};
	for (int i = 0; i < numberOfAlgorithms; i++)
	{
		wins[i] = new int[mapSizes] {};
	}

	// Repeat mapsPerSize times. This is outside the mapSizes loop because doing all of one size's tests before starting another size increases chances that the results will be impacted by changing external conditions.
	for (int m = 0, totalJourneys = 0; m < mapsPerSize; m++)
	{
		// For each map size
		for (int s = 0; s < mapSizes; s++)
		{
			int mapSize = firstMapSize + s * mapSizeInterval;
			cout << "Map " << m * mapSizes + s + 1 << ", Size " << mapSize << "x" << mapSize << ", Testing " << journeysPerMap << " journeys";

			// Generate map
			Map map(Vector2i(mapSize, mapSize));
			map.generateObstacles();

			// Repeat journeysPerMap times
			for (int j = 0; j < journeysPerMap; j++, totalJourneys++)
			{
				cout << ".";

				// Generate start and end coords
				Vector2i start = pickEmptyCoord(map);
				Vector2i end = pickEmptyCoord(map, start);

				int fastestAlgorithm; // The index in the algorithms vector of the algorithm that was fastest
				float shortestTime; // How long it took
				bool isDraw; // Whether it was a draw

				// For each algorithm in the algorithms vector
				for (int a = 0; a < numberOfAlgorithms; a++)
				{
					// "a2" is "a" but shifted. This means the algorithm order changes each journey. The last to be tested seems to perform slightly better
					int a2 = (totalJourneys + a) % numberOfAlgorithms;

					// Run the algorithm and time it
					the_clock::time_point startTime = the_clock::now();
					getPathfinder(algorithms[a2])->generatePath(map, start, end);
					the_clock::time_point endTime = the_clock::now();

					// Store the time in the times array
					float time_taken = (float)duration_cast<nanoseconds>(endTime - startTime).count() / 1000000;
					times[a2][s].push_back(time_taken);

					// If it's the fastest so far
					if (a == 0 || time_taken < shortestTime)
					{
						fastestAlgorithm = a2;
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
					// Increment the algorithm's win count in the wins array
					wins[fastestAlgorithm][s]++;
				}
			}
			cout << endl;
		}
	}
	cout << endl;

	// Create CSV file
	string filePath = "Test Results/";
	// Give it a name like (algorithm 1) vs (algorithm 2) etc
	for (int a = 0; a < numberOfAlgorithms; a++)
	{
		if (a > 0) filePath += " vs ";
		filePath += getAlgorithmName(algorithms[a]);
	}
	filePath += ".csv";
	ofstream my_file(filePath);
	cout << "Writing results to " << filePath << " (If no Test Results directory exists the results will not be saved)" << endl;

	// Write details of test to file
	my_file << "Map sizes, " << mapSizes << endl;
	my_file << "Maps per size, " << mapsPerSize << endl;
	my_file << "Journeys per map, " << journeysPerMap << endl;
	int journeysPerMapSize = mapsPerSize * journeysPerMap;
	my_file << "Journeys per map size, " << journeysPerMapSize << endl;

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
			float medianTime = times[a][s][journeysPerMapSize / 2];
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
				float winPercent = (float)wins[a][s] / journeysPerMapSize * 100;
				my_file << ", " << winPercent;
			}
			my_file << endl;
		}
	}

	// Write all times to file
	my_file << endl;
	my_file << "Time to find Shortest Path vs. Map Size" << endl;
	// Write the map sizes
	my_file << "Map Size" << endl;
	for (int s = 0, mapSize = firstMapSize; s < mapSizes; s++, mapSize += mapSizeInterval)
	{
		if (s > 0) my_file << ", ";
		my_file << mapSize;
	}
	my_file << endl;
	// Write the times for each algorithm
	for (int a = 0; a < numberOfAlgorithms; a++)
	{
		my_file << getAlgorithmName(algorithms[a]) << endl;
		for (int i = 0; i < journeysPerMapSize; i++)
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


// Returns a pointer to the Pathfinder corresponding to an Algorithm enum
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


// Returns the name corresponding to an Algorithm enum
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


// Returns a random coordinate of a map that is empty
Vector2i AlgorithmTester::pickEmptyCoord(const Map& map)
{
	while (true)
	{
		Vector2i coord = Vector2i(rand() % map.getSize().x, rand() % map.getSize().y);
		if (map.getValue(coord) == 0) { return coord; }
	}
}


// Returns a random coordinate of a map that is empty and not equal to invalidCoord. Used for picking an end point that isn't the same as the start point
Vector2i AlgorithmTester::pickEmptyCoord(const Map& map, Vector2i invalidCoord)
{
	while (true)
	{
		Vector2i coord = Vector2i(rand() % map.getSize().x, rand() % map.getSize().y);
		if (map.getValue(coord) == 0 && coord != invalidCoord) { return coord; }
	}
}
