#include "AlternateAStarOpenSet.h"

#include <algorithm> // find_if


AlternateAStarOpenSet::AlternateAStarOpenSet()
{
}


AlternateAStarOpenSet::~AlternateAStarOpenSet()
{
}


bool AlternateAStarOpenSet::isEmpty()
{
	return set.empty();
}


void AlternateAStarOpenSet::deleteNode(std::vector<AStarNode*>::iterator it)
{
	delete* it;
	set.erase(it);
}


void AlternateAStarOpenSet::deleteAll()
{
	for (auto node : set)
	{
		delete node;
	}
	set.clear();
}


AStarNode* AlternateAStarOpenSet::getBackNode()
{
	return set.back();
}


void AlternateAStarOpenSet::popBack()
{
	set.pop_back();
}


// Insert the node into the open set in descending order of f
void AlternateAStarOpenSet::insertOrdered(AStarNode* node)
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


std::vector<AStarNode*>::iterator AlternateAStarOpenSet::findNode(Vector2i coord)
{
	//for (auto it = set.begin(); it != set.end(); it++)
	//{
	//	if ((*it)->coord == coord) return it;
	//}
	//return set.end();

	return find_if(set.begin(), set.end(), [coord](AStarNode* n) { return n->coord == coord; });
}


bool AlternateAStarOpenSet::isEnd(std::vector<AStarNode*>::iterator it)
{
	return it == set.end();
}


const std::vector<AStarNode*>* AlternateAStarOpenSet::getSet() const
{
	return &set;
}