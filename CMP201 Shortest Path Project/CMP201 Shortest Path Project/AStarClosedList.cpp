#include "AStarClosedList.h"

#include <algorithm> // find_if


AStarClosedList::AStarClosedList()
{
}


AStarClosedList::~AStarClosedList()
{
}


void AStarClosedList::addNode(AStarNode* node)
{
	list.push_back(node);
}


bool AStarClosedList::containsCoord(Vector2i coord)
{
	return find_if(list.begin(), list.end(), [coord](AStarNode * s) { return s->coord == coord; }) != list.end();
}


void AStarClosedList::deleteAll()
{
	for (auto node : list)
	{
		delete node;
	}
	list.clear();
}
