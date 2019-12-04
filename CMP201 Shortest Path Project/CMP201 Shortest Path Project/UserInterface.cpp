#include "UserInterface.h"

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
using namespace std;

#include "Vector2i.h"


UserInterface::UserInterface(AlgorithmTester* _algorithmTester) : algorithmTester(_algorithmTester)
{
}


UserInterface::~UserInterface()
{
}


void UserInterface::beginSession()
{
	cout << "Matt's pathfinding algorithm tester\n";

	mainMenu();
}


void UserInterface::mainMenu()
{
	while (true)
	{
		cout << "MAIN MENU\n";
		cout << "1: Visualize algorithm\n";
		cout << "2: Benchmark algorithms\n";
		cout << "3: Quit\n";

		int input = getIntInput(1, 3);

		if (input == 1) visualizeAlgorithm();
		else if (input == 2) benchmarkAlgorithms();
		else if (input == 3) return;
	}
}


void UserInterface::visualizeAlgorithm()
{
	cout << "Please choose an algorithm.\n";
	Algorithm algorithm = selectAlgorithm();

	cout << "Please enter map size.\n";
	int mapSize = getIntInput(10, 1000);

	while (true)
	{
		algorithmTester->visualizeAlgorithm(algorithm, mapSize);
		cout << "\n";

		cout << "Run algorithm again?\n";
		cout << "1: Yes\n";
		cout << "2: No\n";

		int input = getIntInput(1, 2);

		if (input == 2) return;
	}
}


void UserInterface::benchmarkAlgorithms()
{
	cout << "How many algorithms would you like to benchmark?\n";
	int numberOfAlgorithms = getIntInput(1, 4);

	vector<Algorithm> algorithms;
	if (numberOfAlgorithms == 1)
	{
		cout << "Please choose an algorithm.\n";
		algorithms.push_back(selectAlgorithm());
	}
	else
	{
		for (int a = 0; a < numberOfAlgorithms; a++)
		{
			cout << "Please choose algorithm " << a + 1 << ".\n";
			algorithms.push_back(selectAlgorithm());
		}
	}

	cout << "Please enter the number of map sizes.\n";
	int numberOfMapSizes = getIntInput(1, 100);

	int firstMapSize;
	int mapSizeInterval = 0;
	if (numberOfMapSizes == 1)
	{
		cout << "Please enter the map size.\n";
		firstMapSize = getIntInput(10, 10000);
	}
	else
	{
		cout << "Please enter the first map size.\n";
		firstMapSize = getIntInput(10, 10000);

		cout << "Please enter the map size interval.\n";
		mapSizeInterval = getIntInput(1, 1000);
	}

	cout << "Please enter number of random maps per size.\n";
	int maps = getIntInput(1, 1000);

	cout << "Please enter number of random routes per map.\n";
	int routes = getIntInput(1, 1000);

	cout << "Please enter number of tests per route. Higher values reduce ms rounding error.\n";
	int iterations = getIntInput(1, 1000);

	while (true)
	{
		algorithmTester->benchmarkAlgorithms(algorithms, numberOfMapSizes, firstMapSize, mapSizeInterval, maps, routes, iterations);
		cout << "\n";

		cout << "Run test again?\n";
		cout << "1: Yes\n";
		cout << "2: No\n";

		int input = getIntInput(1, 2);

		if (input == 2) return;
	}
}


// Gets the users input as an int. Rejects inputs outside the specified range. Non-int values are converted to 0.
int UserInterface::getIntInput(int min, int max)
{
	while (true)
	{
		int input;
		cin >> input;

		// Handle non-int inputs
		cin.clear(); // Clear the error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any input waiting in the stream

		if (input < min || input > max)
		{
			cout << "Input not valid. Please enter a number in the range " << min << " to " << max << ".\n";
		}
		else
		{
			cout << "\n";
			return input;
		}
	}
}


Algorithm UserInterface::selectAlgorithm()
{
	while (true)
	{
		cout << "1: Lee\n";
		cout << "2: Dijkstra\n";
		cout << "3: A*\n";
		cout << "4: A* alternate\n";

		int input = getIntInput(1, 4);

		if (input == 1) return Algorithm::Lee;
		else if (input == 2) return Algorithm::Dijkstra;
		else if (input == 3) return Algorithm::AStar;
		else if (input == 4) return Algorithm::AStarAlternate;
	}
}