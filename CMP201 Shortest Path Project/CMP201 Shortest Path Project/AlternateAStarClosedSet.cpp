#include "AlternateAStarClosedSet.h"

#include <algorithm> // find_if


AlternateAStarClosedSet::AlternateAStarClosedSet()
{
}


AlternateAStarClosedSet::~AlternateAStarClosedSet()
{
}


void AlternateAStarClosedSet::addNode(AStarNode* node)
{
	// Calculate a hash unique to the node's position
	node->positionHash = node->coord.y * mapWidth + node->coord.x;

	// Use a binary search to find the first node in the set with a positionHash greater than or equal to the node's positionHash
	auto it = std::lower_bound(set.begin(), set.end(), node, [](AStarNode* lhs, AStarNode* rhs) -> bool { return lhs->positionHash < rhs->positionHash; });

	set.insert(it, node);
}


// Return true if the set contains a node with the specified coordinate
bool AlternateAStarClosedSet::contains(Vector2i coord)
{
	// Calculate a hash unique to the coordinate
	int positionHash = coord.y * mapWidth + coord.x;

	// Use a binary search to find the first node in the set with a positionHash greater than or equal to the coordinate's positionHash
	auto it = std::lower_bound(set.begin(), set.end(), positionHash, [](AStarNode* lhs, int rhs) -> bool { return lhs->positionHash < rhs; });

	// Return true if the positionHash from the set matches the coordinate's positionHash
	return it != set.end() && (*it)->positionHash == positionHash;
}


void AlternateAStarClosedSet::deleteAll()
{
	for (auto node : set)
	{
		delete node;
	}
	set.clear();
}


const std::vector<AStarNode*>* AlternateAStarClosedSet::getSet() const
{
	return &set;
}
