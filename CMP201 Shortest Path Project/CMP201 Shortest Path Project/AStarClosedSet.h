#pragma once

#include "AStarNode.h"
#include <vector>


// The closed set used by AStarPathfinder


class AStarClosedSet
{
public:
	AStarClosedSet();
	~AStarClosedSet();

	void addNode(AStarNode* node);
	bool contains(Vector2i coord);
	void deleteAll();
	void setMapWidth(int _mapWidth) { mapWidth = _mapWidth; }

	// Used for displaying the set
	const std::vector<AStarNode*>* getSet() const;

private:
	std::vector<AStarNode*> set;
	int mapWidth = 0;
};

