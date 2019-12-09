#pragma once

#include "DijkstraNode.h"
#include <vector>


// The closed set used by DijkstraPathfinder


class DijkstraClosedSet
{
public:
	DijkstraClosedSet();
	~DijkstraClosedSet();

	void addNode(DijkstraNode* node);
	bool contains(Vector2i coord);
	void deleteAll();
	void setMapWidth(int _mapWidth) { mapWidth = _mapWidth; }
	
	// Used for displaying the set
	const std::vector<DijkstraNode*>* getSet() const;

private:
	std::vector<DijkstraNode*> set;
	int mapWidth = 0;
};