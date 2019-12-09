#pragma once

#include "Vector2i.h"


// DijkstraNode is used by DijkstraPathfinder to store information about tiles it has checked.


struct DijkstraNode
{
	DijkstraNode();
	~DijkstraNode();

	float cost = 0;

	Vector2i coord;
	int positionHash;

	DijkstraNode* parent;
};