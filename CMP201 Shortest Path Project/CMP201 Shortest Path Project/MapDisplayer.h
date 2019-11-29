#pragma once

#include "Map.h"
#include "Path.h"
#include "AStarOpenSet.h"
#include "AStarClosedSet.h"


class MapDisplayer
{
public:
	MapDisplayer();
	~MapDisplayer();

	void loadMap(const Map& map);
	void drawPath(const Path& path);
	void drawAStarOpenSet(const AStarOpenSet& openSet);
	void drawAStarClosedSet(const AStarClosedSet& openSet);
	void print();

private:
	Vector2i bufferSize;
	char* charBuffer;
	int* colourBuffer;

	void setChar(Vector2i coords, char character);
	void setColour(Vector2i coords, int colour);
};

