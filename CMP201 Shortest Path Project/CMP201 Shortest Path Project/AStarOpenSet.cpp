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


// Insert the node into the open set in descending order of f
void AStarOpenSet::insertOrdered(AStarNode* node)
{
	// Linear search
	for (std::vector<AStarNode*>::iterator it = set.begin(); it != set.end(); it++)
	{
		if ((*it)->f < node->f)
		{
			set.insert(it, node);
			return;
		}
	}
	set.push_back(node);

	// Binary search
	//auto it = std::lower_bound(set.begin(), set.end(), node->f, [](AStarNode* lhs, float rhs) -> bool { return lhs->f > rhs; });
	//set.insert(it, node);
}


std::vector<AStarNode*>::iterator AStarOpenSet::findNode(Vector2i coord)
{
	//for (auto it = set.begin(); it != set.end(); it++)
	//{
	//	if ((*it)->coord == coord) return it;
	//}
	//return set.end();

	return find_if(set.begin(), set.end(), [coord](AStarNode* n) { return n->coord == coord; });
}


bool AStarOpenSet::isEnd(std::vector<AStarNode*>::iterator it)
{
	return it == set.end();
}


const std::vector<AStarNode*>* AStarOpenSet::getSet() const
{
	return &set;
}