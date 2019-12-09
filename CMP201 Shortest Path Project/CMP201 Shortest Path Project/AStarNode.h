#pragma once

#include "Vector2i.h"


// AStarNode is used by AStarPathfinder to store information about tiles it has checked.


struct AStarNode
{
	AStarNode();
	~AStarNode();

	float f = 0;
	float g = 0;
	float h = 0;

	Vector2i coord;
	int positionHash;

	AStarNode* parent;
};

