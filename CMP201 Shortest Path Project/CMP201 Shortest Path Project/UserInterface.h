#pragma once

#include "Map.h"
#include "MapDisplayer.h"
#include "AStarPathfinder.h"


class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void beginSession();

private:
	MapDisplayer mapDisplayer;
	AStarPathfinder aStarPathfinder;
};

