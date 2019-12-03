#include "DijkstraOpenSet.h"

#include <algorithm> // find_if


DijkstraOpenSet::DijkstraOpenSet()
{
}


DijkstraOpenSet::~DijkstraOpenSet()
{
}


bool DijkstraOpenSet::isEmpty()
{
	return set.empty();
}


void DijkstraOpenSet::deleteNode(std::vector<DijkstraNode*>::iterator it)
{
	delete* it;
	set.erase(it);
}


void DijkstraOpenSet::deleteAll()
{
	for (auto node : set)
	{
		delete node;
	}
	set.clear();
}


DijkstraNode* DijkstraOpenSet::getBackNode()
{
	return set.back();
}


void DijkstraOpenSet::popBack()
{
	set.pop_back();
}


// Insert the node into the open set in descending order of cost
void DijkstraOpenSet::insertOrdered(DijkstraNode* node)
{
	// Linear search
	for (std::vector<DijkstraNode*>::iterator it = set.begin(); it != set.end(); it++)
	{
		if ((*it)->cost < node->cost)
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


std::vector<DijkstraNode*>::iterator DijkstraOpenSet::findNode(Vector2i coord)
{
	//for (auto it = set.begin(); it != set.end(); it++)
	//{
	//	if ((*it)->coord == coord) return it;
	//}
	//return set.end();

	return find_if(set.begin(), set.end(), [coord](DijkstraNode* n) { return n->coord == coord; });
}


bool DijkstraOpenSet::isEnd(std::vector<DijkstraNode*>::iterator it)
{
	return it == set.end();
}


const std::vector<DijkstraNode*>* DijkstraOpenSet::getSet() const
{
	return &set;
}