#pragma once

#include "Map.h"
#include "Path.h"
#include <string>


class MapDisplayer
{
public:
	MapDisplayer();
	~MapDisplayer();

	void loadMap(const Map& map);
	void loadPath(const Path& path);
	void setChar(Vector2i coord, char character);
	void setInt(Vector2i coord, int i);
	void setColour(Vector2i coord, int colour);

	void print();

private:
	Vector2i bufferSize;
	// Values below 128 in the int buffer refer to ASCII chars. Values 128 and up represent numbers, starting from 128 = 0.
	int* intBuffer;
	int* colourBuffer;
};

