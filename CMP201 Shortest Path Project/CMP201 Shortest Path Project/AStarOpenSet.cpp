#include "AStarOpenSet.h"

#include <algorithm> // find_if


AStarOpenSet::AStarOpenSet()
{
}


AStarOpenSet::~AStarOpenSet()
{
}


bool AStarOpenSet::isEmpty()
{
	return set.empty();
}


void AStarOpenSet::deleteNode(std::vector<AStarNode*>::iterator it)
{
	delete *it;
	set.erase(it);
}


void AStarOpenSet::deleteAll()
{
	for (auto node : set)
	{
		delete node;
	}
	set.clear();
}


AStarNode* AStarOpenSet::getBackNode()
{
	return set.back();
}


void AStarOpenSet::popBack()
{
	set.pop_back();
}


void AStarOpenSet::insertOrdered(AStarNode* node)
{
	// Maybe use upper_bound for this?

	// Iterate from the back to the start, cause it's likely to be near the back considering it's a neighbour of the node with the lowest f value
	for (std::vector<AStarNode*>::iterator it = set.end(); it != set.begin(); it--)
	{
		// If previous element has a higher f, insert
		if ((*(it - 1))->f > node->f)
		{
			set.insert(it, node);
			return;
		}
	}
	set.insert(set.begin(), node);

}


bool AStarOpenSet::contains(Vector2i coord)
{
	return !iteratorIsEnd(findNode(coord));
}


std::vector<AStarNode*>::iterator AStarOpenSet::findNode(Vector2i coord)
{
	// Maybe search from back to front cause find_if does the opposite
	return find_if(set.begin(), set.end(), [coord](AStarNode* s) { return s->coord == coord; });
}


bool AStarOpenSet::iteratorIsEnd(std::vector<AStarNode*>::iterator it)
{
	return it == set.end();
}


const std::vector<AStarNode*>* AStarOpenSet::getSet() const
{
	return &set;
}