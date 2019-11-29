#pragma once

#include "AStarNode.h"
#include <vector>


class AStarClosedList
{
public:
	AStarClosedList();
	~AStarClosedList();

	void addNode(AStarNode* node);
	bool containsCoord(Vector2i coord);

	void deleteAll();


private:
	std::vector<AStarNode*> list;
};

