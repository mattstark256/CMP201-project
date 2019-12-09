#include "DijkstraPathfinder.h"

#include <stdlib.h> // abs
#include <algorithm> // min, max
using namespace std; // min, max


DijkstraPathfinder::DijkstraPathfinder()
{
}


DijkstraPathfinder::~DijkstraPathfinder()
{
}


// Search for a path between the start and end points using the Dijkstra algorithm. If mapDisplayer is not nullptr, display the results.
Path DijkstraPathfinder::generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer)
{
	// This is used for calculating position hashes
	closedSet.setMapWidth(map.getSize().x);

	// Set up the start node
	DijkstraNode* startNode = new DijkstraNode();
	startNode->coord = start;
	startNode->parent = nullptr;
	openSet.insertOrdered(startNode);

	DijkstraNode* endNode = nullptr;

	bool pathFound = false;
	while (!openSet.isEmpty())
	{
		// Get the node with the smallest cost value
		DijkstraNode* current = openSet.getBackNode();

		// If a path to the end has been found
		if (current->coord == end)
		{
			pathFound = true;
			endNode = current;
			break;
		}

		// Move the current node from the open set to the closed set
		openSet.popBack();
		closedSet.addNode(current);

		// For each movement direction
		for (int i = 0; i < MOVEMENT_DIRECTIONS; i++)
		{
			Vector2i neighbourCoord(current->coord.x + xOffsets[i], current->coord.y + yOffsets[i]);

			if (current->parent != nullptr)
			{
				// If it's backtracking, skip it
				if (neighbourCoord == current->parent->coord) { continue; }

				// If it's orthogonally adjacent to the parent, skip it
				// If this is the case, it'll always be faster to go there directly from the parent
				float dx = abs(neighbourCoord.x - current->parent->coord.x);
				float dy = abs(neighbourCoord.y - current->parent->coord.y);
				if (dx == 0 && dy == 1 || dx == 1 && dy == 0) { continue; }
			}

			// If the neighbour is outside the map, skip it
			if (!map.isWithinMap(neighbourCoord)) { continue; }

			// If the route to the neighbour is blocked, skip it
			// A diagonal route can be blocked by adjacent obstacles with corners intersecting the route
			if (map.getValue(neighbourCoord) == 1 ||
				isDiagonal[i] && (map.getValue(Vector2i(neighbourCoord.x, current->coord.y)) == 1 || map.getValue(Vector2i(current->coord.x, neighbourCoord.y)) == 1))
			{
				continue;
			}

			// If the neighbour is on the closed list, skip it
			if (closedSet.contains(neighbourCoord)) { continue; }

			// Calculate the neighbour's cost
			float newCost = current->cost + distances[i];

			// If it's in the open list
			std::vector<DijkstraNode*>::iterator it = openSet.findNode(neighbourCoord);
			if (!openSet.isEnd(it))
			{
				if ((*it)->cost <= newCost)
				{
					// If the node in the open list has a better or equal cost, we don't need to replace it.
					continue;
				}
				else
				{
					// If the node in the open list has a worse cost, we need to replace it.
					// We'll be calculating a new value for cost so it'll need to be re-inserted to maintain the correct list order
					openSet.deleteNode(it);
				}
			}

			// Create a new node and insert it into the open set
			DijkstraNode* neighbourNode = new DijkstraNode();
			neighbourNode->coord = neighbourCoord;
			neighbourNode->cost = newCost;
			neighbourNode->parent = current;
			openSet.insertOrdered(neighbourNode);
		}
	}

	// Create a path. Start from the end node and follow each node's parent back to the start
	Path path(start, end);
	if (pathFound)
	{
		path.setConnected(true);
		DijkstraNode* current = endNode->parent;
		while (true)
		{
			if (current == startNode) { break; }
			path.addPathCoord(current->coord);
			current = current->parent;
		}
	}

	// If a mapDisplayer was provided, display the results
	if (mapDisplayer != nullptr)
	{
		mapDisplayer->loadMap(map);

		// Draw the open set
		for (auto node : *openSet.getSet())
		{
			mapDisplayer->setChar(node->coord, 'o');
			mapDisplayer->setColour(node->coord, 0x0004);
		}
		// Draw the closed set
		for (auto node : *closedSet.getSet())
		{
			mapDisplayer->setChar(node->coord, '.');
			mapDisplayer->setColour(node->coord, 0x0004);
		}

		mapDisplayer->drawPath(path);
		mapDisplayer->print();
	}

	openSet.deleteAll();
	closedSet.deleteAll();

	return path;
}