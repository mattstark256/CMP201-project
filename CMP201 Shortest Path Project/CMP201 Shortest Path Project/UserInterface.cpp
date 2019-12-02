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
		cout << "2: Test algorithm performance\n";
		cout << "3: Test algorithm performance head to head\n";
		cout << "4: Test algorithm performance against map size\n";
		cout << "5: Test algorithm performance against map size head to head\n";
		cout << "6: Quit\n";

		int input = getIntInput();

		if (input == 1) visualizeAlgorithm();
		else if (input == 2) testAlgorithmPerformance();
		else if (input == 3) testAlgorithmPerformanceHeadToHead();
		else if (input == 4) testAlgorithmPerformanceVsMapSize();
		else if (input == 5) testAlgorithmPerformanceVsMapSizeHeadToHead();
		else if (input == 6) return;
	}
}

void UserInterface::visualizeAlgorithm()
{
	cout << "Please choose an algorithm.\n";
	Algorithm algorithm = selectAlgorithm();

	cout << "Please enter map size.\n";
	int mapSize = getIntInput();

	while (true)
	{
		algorithmTester->visualizeAlgorithm(algorithm, mapSize);
		cout << "\n";

		while (true)
		{
			cout << "Run algorithm again?\n";
			cout << "1: Yes\n";
			cout << "2: No\n";

			int input = getIntInput();

			if (input == 1) break;
			else if (input == 2) return;
		}
	}
}


void UserInterface::testAlgorithmPerformance()
{
	cout << "Please choose an algorithm.\n";
	Algorithm algorithm = selectAlgorithm();

	cout << "Please enter map size.\n";
	int mapSize = getIntInput();

	cout << "Please enter number of random maps.\n";
	int maps = getIntInput();

	cout << "Please enter number of random routes per map.\n";
	int routes = getIntInput();

	cout << "Please enter number of iterations per route. Higher values reduce ms rounding error.\n";
	int iterations = getIntInput();

	while (true)
	{
		algorithmTester->testAlgorithm(algorithm, mapSize, maps, routes, iterations);
		cout << "\n";

		while (true)
		{
			cout << "Run test again?\n";
			cout << "1: Yes\n";
			cout << "2: No\n";

			int input = getIntInput();

			if (input == 1) break;
			else if (input == 2) return;
		}
	}
}


void UserInterface::testAlgorithmPerformanceHeadToHead()
{
	cout << "Please choose the first algorithm.\n";
	Algorithm algorithm1 = selectAlgorithm();

	cout << "Please choose the second algorithm.\n";
	Algorithm algorithm2 = selectAlgorithm();

	cout << "Please enter map size.\n";
	int mapSize = getIntInput();

	cout << "Please enter number of random maps.\n";
	int maps = getIntInput();

	cout << "Please enter number of random routes per map.\n";
	int routes = getIntInput();

	cout << "Please enter number of iterations per route. Higher values reduce ms rounding error.\n";
	int iterations = getIntInput();

	while (true)
	{
		algorithmTester->testAlgorithmsHeadToHead(algorithm1, algorithm2, mapSize, maps, routes, iterations);
		cout << "\n";

		while (true)
		{
			cout << "Run test again?\n";
			cout << "1: Yes\n";
			cout << "2: No\n";

			int input = getIntInput();

			if (input == 1) break;
			else if (input == 2) return;
		}
	}
}


void UserInterface::testAlgorithmPerformanceVsMapSize()
{
	cout << "Please choose an algorithm.\n";
	Algorithm algorithm = selectAlgorithm();

	cout << "Please enter the number of map sizes.\n";
	int numberOfMapSizes = getIntInput();

	cout << "Please enter the first map size.\n";
	int firstMapSize = getIntInput();

	cout << "Please enter the map size interval.\n";
	int mapSizeInterval = getIntInput();

	cout << "Please enter number of random maps per size.\n";
	int maps = getIntInput();

	cout << "Please enter number of random routes per map.\n";
	int routes = getIntInput();

	cout << "Please enter number of iterations per route. Higher values reduce ms rounding error.\n";
	int iterations = getIntInput();

	while (true)
	{
		algorithmTester->testAlgorithmPerformanceVsMapSize(algorithm, numberOfMapSizes, firstMapSize, mapSizeInterval, maps, routes, iterations);
		cout << "\n";

		while (true)
		{
			cout << "Run test again?\n";
			cout << "1: Yes\n";
			cout << "2: No\n";

			int input = getIntInput();

			if (input == 1) break;
			else if (input == 2) return;
		}
	}
}

void UserInterface::testAlgorithmPerformanceVsMapSizeHeadToHead()
{
	cout << "Please choose the first algorithm.\n";
	Algorithm algorithm1 = selectAlgorithm();

	cout << "Please choose the second algorithm.\n";
	Algorithm algorithm2 = selectAlgorithm();

	cout << "Please enter the number of map sizes.\n";
	int numberOfMapSizes = getIntInput();

	cout << "Please enter the first map size.\n";
	int firstMapSize = getIntInput();

	cout << "Please enter the map size interval.\n";
	int mapSizeInterval = getIntInput();

	cout << "Please enter number of random maps per size.\n";
	int maps = getIntInput();

	cout << "Please enter number of random routes per map.\n";
	int routes = getIntInput();

	cout << "Please enter number of iterations per route. Higher values reduce ms rounding error.\n";
	int iterations = getIntInput();

	while (true)
	{
		algorithmTester->testAlgorithmsHeadToHeadPerformanceVsMapSize(algorithm1, algorithm2, numberOfMapSizes, firstMapSize, mapSizeInterval, maps, routes, iterations);
		cout << "\n";

		while (true)
		{
			cout << "Run test again?\n";
			cout << "1: Yes\n";
			cout << "2: No\n";

			int input = getIntInput();

			if (input == 1) break;
			else if (input == 2) return;
		}
	}
}


// Gets the users input as an int. Non-int values return 0.
int UserInterface::getIntInput()
{
	int input;
	cin >> input;
	cout << "\n";

	// Handle non-int inputs
	cin.clear(); // Clear the error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any input waiting in the stream

	return input;
}


Algorithm UserInterface::selectAlgorithm()
{
	while (true)
	{
		cout << "1: Lee\n";
		cout << "2: Dijkstra\n";
		cout << "3: A*\n";
		cout << "4: A* alternate\n";

		int input = getIntInput();

		if (input == 1) return Algorithm::Lee;
		else if (input == 2) return Algorithm::Dijkstra;
		else if (input == 3) return Algorithm::AStar;
		else if (input == 4) return Algorithm::AStarAlternate;
	}
}

void UserInterface::printAlgorithmName(Algorithm algorithm)
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
