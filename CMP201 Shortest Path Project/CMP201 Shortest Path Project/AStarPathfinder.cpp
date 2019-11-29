#include "AStarPathfinder.h"

#include <stdlib.h> // abs
#include <algorithm> // min, max


AStarPathfinder::AStarPathfinder()
{
}


AStarPathfinder::~AStarPathfinder()
{
}

Path AStarPathfinder::generatePath(const Map& map, Vector2i start, Vector2i end)
{
	Path path(start, end);

	AStarNode* startNode = new AStarNode();
	startNode->coord = start;
	startNode->f = getHeuristic(start, end);
	openList.insertOrdered(startNode);

	AStarNode* endNode = nullptr;

	bool pathFound = false;
	while (!openList.isEmpty())
	{
		AStarNode* current = openList.getBackNode();

		if (current->coord == end)
		{
			// Path has been found
			pathFound = true;
			endNode = current;
			break;
		}

		openList.popBack();
		closedList.addNode(current);

		for (int i = 0; i < MOVEMENT_DIRECTIONS; i++)
		{
			Vector2i neighbourCoord(current->coord.x + xOffsets[i], current->coord.y + yOffsets[i]);

			// If the neighbour is outside the map, skip it
			if (!map.isWithinMap(neighbourCoord)) { continue; }

			// If the route to the neighbour is blocked, skip it
			// A diagonal route can be blocked by adjacent obstacles with corners intersecting the route
			if (map.getValue(neighbourCoord) == 1 ||
				isDiagonal[i] && (map.getValue(Vector2i(neighbourCoord.x, current->coord.y)) == 1 || map.getValue(Vector2i(current->coord.x, neighbourCoord.y)) == 1))
			{ continue; }

			// If the neighbour is on the closed list, skip it
			if (closedList.containsCoord(neighbourCoord)) { continue; }

			float new_g = current->g + distances[i];

			// If it's in the open list
			std::vector<AStarNode*>::iterator it = openList.findNode(neighbourCoord);
			if (!openList.iteratorIsEnd(it))
			{
				if ((*it)->g < new_g)
				{
					continue;
				}
				else
				{
					// We'll be calculating a new value for f so it'll need to be re-inserted to maintain the correct list order
					openList.deleteNode(it);
				}
			}

			AStarNode* neighbourNode = new AStarNode();
			neighbourNode->coord = neighbourCoord;
			neighbourNode->g = new_g;
			neighbourNode->h = getHeuristic(neighbourCoord, end);
			neighbourNode->f = neighbourNode->g + neighbourNode->h;
			neighbourNode->parent = current;
			openList.insertOrdered(neighbourNode);
		}
	}

	if (pathFound)
	{
		path.setConnected(true);
		AStarNode* current = endNode->parent;
		while (true)
		{
			if (current == startNode) { break; }
			path.addPathCoord(current->coord);
			current = current->parent;
		}
	}

	openList.deleteAll();
	closedList.deleteAll();

	return path;
}



float AStarPathfinder::getHeuristic(Vector2i a, Vector2i b)
{
	float dx = abs(a.x - b.x);
	float dy = abs(a.y - b.y);
	float dMin = std::min(dx, dy);
	float dMax = std::max(dx, dy);
	return dMax + 0.414 * dMin;
}
