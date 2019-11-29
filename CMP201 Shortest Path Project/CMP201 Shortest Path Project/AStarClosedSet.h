#pragma once

#include "AStarNode.h"
#include <vector>


class AStarClosedSet
{
public:
	AStarClosedSet();
	~AStarClosedSet();

	void addNode(AStarNode* node);
	bool contains(Vector2i coord);
	void deleteAll();

	// Used for displaying the set
	const std::vector<AStarNode*>* getSet() const;

private:
	std::vector<AStarNode*> set;
};

