#pragma once

#include "Vector2i.h"


class Map
{
public:
	Map(Vector2i _size);
	~Map();

	int getValue(const Vector2i& coord);
	void setValue(const Vector2i& coord, int value);
	bool isWithinMap(const Vector2i& coord);

private:
	int* mapValues;
	Vector2i size;
};

