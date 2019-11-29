#pragma once

#include "Vector2i.h"


class Map
{
public:
	Map(Vector2i _size);
	~Map();

	int getValue(Vector2i coord) const;
	void setValue(Vector2i coord, int value);
	bool isWithinMap(Vector2i coord) const;
	const Vector2i& getSize() const;

	void generateObstacles();

private:
	int* mapValues;
	Vector2i size;
};

