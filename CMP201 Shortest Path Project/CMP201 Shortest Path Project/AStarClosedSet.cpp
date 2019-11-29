#include "AStarClosedSet.h"

#include <algorithm> // find_if


AStarClosedSet::AStarClosedSet()
{
}


AStarClosedSet::~AStarClosedSet()
{
}


void AStarClosedSet::addNode(AStarNode* node)
{
	set.push_back(node);
}


bool AStarClosedSet::contains(Vector2i coord)
{
	return find_if(set.begin(), set.end(), [coord](AStarNode * s) { return s->coord == coord; }) != set.end();
}


void AStarClosedSet::deleteAll()
{
	for (auto node : set)
	{
		delete node;
	}
	set.clear();
}


const std::vector<AStarNode*>* AStarClosedSet::getSet() const
{ 
	return &set;
}
