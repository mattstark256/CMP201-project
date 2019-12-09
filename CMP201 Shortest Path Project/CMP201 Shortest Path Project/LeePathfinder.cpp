#include "LeePathfinder.h"



LeePathfinder::LeePathfinder()
{
}


LeePathfinder::~LeePathfinder()
{
}


// Search for a path between the start and end points using the Lee algorithm. If mapDisplayer is not nullptr, display the results.
Path LeePathfinder::generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer)
{
	// Create an array representing the path distance to each tile from the start point
	int* distances = new int[map.getSize().x * map.getSize().y]{};

	// Unassigned distance values are zero. I set the start tile to 1 to distinguish it from unassigned tiles.
	distances[start.y * map.getSize().x + start.x] = 1;

	bool pathFound = false;
	int i = 1; // The distance we are currently looking for
	while (!pathFound)
	{
		int tilesFound = 0;

		// For each tile on the map
		for (int y = 0, j = 0; y < map.getSize().y; y++)
		{
			for (int x = 0; x < map.getSize().x; x++, j++)
			{
				if (distances[j] != i) continue;

				// For each direction
				for (int k = 0; k < MOVEMENT_DIRECTIONS; k++)
				{
					Vector2i neighbour(x + xOffsets[k], y + yOffsets[k]);

					// Ignore tiles outside the map
					if (!map.isWithinMap(neighbour)) continue;

					// Ignore tiles that contain obstacles
					if (map.getValue(neighbour) == 1) continue;

					int neighbourDistanceIndex = neighbour.y * map.getSize().x + neighbour.x;

					// Ignore tiles that have already been assigned a distance
					if (distances[neighbourDistanceIndex] != 0) continue;

					distances[neighbourDistanceIndex] = i + 1;
					tilesFound++;
					if (neighbour == end) pathFound = true;
				}
			}
		}

		// Stop searching if no new tiles were found. This means every tile accessible from the start tile has had a distance assigned to it.
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

			// For each direction
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

	// If a mapDisplayer was provided, display the results
	if (mapDisplayer != nullptr)
	{
		mapDisplayer->loadMap(map);

		// Draw distance values for each tile
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

		mapDisplayer->drawPath(path);
		mapDisplayer->print();
	}

	delete[] distances;

	return path;
}
