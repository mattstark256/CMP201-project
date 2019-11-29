#include "UserInterface.h"

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */

#include "Vector2i.h"




UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}


void UserInterface::beginSession()
{
	std::cout << "Session begun\n";

	while (true)
	{
		// Generate map
		Map map(Vector2i(32, 32));
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
		std::cout << "Searching for path...\n";
		Path path = aStarPathfinder.generatePath(map, start, end);

		// Display results
		if (!path.isConnected()) { std::cout << "No path found!\n"; }
		else { std::cout << "Path found!\n"; }
		mapDisplayer.displayMap(map, path);

		std::cout << "Run again?\n";
		std::string s;
		std::cin >> s;
	}
}

