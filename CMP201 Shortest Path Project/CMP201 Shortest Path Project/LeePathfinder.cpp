#include "LeePathfinder.h"



LeePathfinder::LeePathfinder()
{
}


LeePathfinder::~LeePathfinder()
{
}


Path LeePathfinder::generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer)
{
	int* distances = new int[map.getSize().x * map.getSize().y]{};

	// Unassigned distance values are zero. I set the start tile to 1 to distinguish it from unassigned tiles.
	distances[start.y * map.getSize().x + start.x] = 1;

	bool pathFound = false;
	int i = 1;
	while (!pathFound)
	{
		int tilesFound = 0;

		for (int y = 0, j = 0; y < map.getSize().y; y++)
		{
			for (int x = 0; x < map.getSize().x; x++, j++)
			{
				if (distances[j] != i) continue;

				for (int k = 0; k < MOVEMENT_DIRECTIONS; k++)
				{
					Vector2i neighbour(x + xOffsets[k], y + yOffsets[k]);


					if (!map.isWithinMap(neighbour)) continue;

					if (map.getValue(neighbour) == 1) continue;

					int neighbourDistanceIndex = neighbour.y * map.getSize().x + neighbour.x;

					if (distances[neighbourDistanceIndex] != 0) continue;

					distances[neighbourDistanceIndex] = i + 1;
					tilesFound++;
					if (neighbour == end) pathFound = true;
				}
			}
		}

		if (tilesFound == 0) break;
		i++;
	}

	Path path(start, end);

	// Trace back from the end to find the shortest path 
	if (pathFound)
	{
		Vector2i current = end;

		for (int i = distances[end.y * map.getSize().x + end.x] - 1; i > 1; i--)
		{
			Vector2i next;
			for (int k = 0; k < MOVEMENT_DIRECTIONS; k++)
			{
				Vector2i neighbour(current.x + xOffsets[k], current.y + yOffsets[k]);
				if (!map.isWithinMap(neighbour)) continue;
				if (distances[neighbour.y * map.getSize().x + neighbour.x] == i)
				{
					next = neighbour;
				}
			}
			current = next;
			path.addPathCoord(current);
		}
	}

	// Display the path
	if (mapDisplayer != nullptr)
	{
		mapDisplayer->loadMap(map);

		for (int y = 0, j = 0; y < map.getSize().y; y++)
		{
			for (int x = 0; x < map.getSize().x; x++, j++)
			{
				int distance = distances[y * map.getSize().x + x];
				if (distance != 0)
				{
					mapDisplayer->setInt(Vector2i(x, y), distance - 1);
					mapDisplayer->setColour(Vector2i(x, y), 0x0004);
				}
			}
		}

		mapDisplayer->loadPath(path);
		mapDisplayer->print();
	}

	delete[] distances;

	return path;
}
