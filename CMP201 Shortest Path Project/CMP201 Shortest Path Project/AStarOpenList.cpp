#include "AStarOpenList.h"

#include <algorithm> // find_if

#include <iostream>

AStarOpenList::AStarOpenList()
{
}


AStarOpenList::~AStarOpenList()
{
}


void AStarOpenList::deleteNode(std::vector<AStarNode*>::iterator it)
{
	delete *it;
	list.erase(it);
}


AStarNode* AStarOpenList::getBackNode()
{
	return list.back();
}


void AStarOpenList::popBack()
{
	list.pop_back();
}


void AStarOpenList::insertOrdered(AStarNode* node)
{
	// Maybe use upper_bound for this?

	// Iterate from the back to the start, cause it's likely to be near the back considering it's a neighbour of the node with the lowest f value
	for (std::vector<AStarNode*>::iterator it = list.end(); it != list.begin(); it--)
	{
		// If previous element has a higher f, insert
		if ((*(it - 1))->f > node->f)
		{
			list.insert(it, node);
			return;
		}
	}
	list.insert(list.begin(), node);

}


std::vector<AStarNode*>::iterator AStarOpenList::findNode(Vector2i coord)
{
	// Maybe search from back to front cause find_if does the opposite
	return find_if(list.begin(), list.end(), [coord](AStarNode* s) { return s->coord == coord; });
}


bool AStarOpenList::iteratorIsEnd(std::vector<AStarNode*>::iterator it)
{
	return it == list.end();
}


void AStarOpenList::deleteAll()
{
	for (auto node : list)
	{
		delete node;
	}
	list.clear();
}

bool AStarOpenList::isEmpty()
{
	return list.empty();
}
