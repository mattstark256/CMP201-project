#pragma once

#include "Vector2i.h"


struct DijkstraNode
{
	DijkstraNode();
	~DijkstraNode();

	float cost = 0;

	Vector2i coord;
	int positionHash;

	DijkstraNode* parent;
};