#pragma once

#include "Map.h"
#include "Path.h"


class MapDisplayer
{
public:
	MapDisplayer();
	~MapDisplayer();

	void displayMap(const Map& map, const Path& path);
};

