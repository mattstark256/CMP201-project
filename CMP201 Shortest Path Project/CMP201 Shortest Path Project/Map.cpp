#include "Map.h"

#include <stdlib.h>     /* srand, rand */


Map::Map(Vector2i _size) : size(_size)
{
	mapValues = new int[size.x * size.y]{};
}


Map::~Map()
{
	delete[] mapValues;
}


int Map::getValue(Vector2i coord) const
{
	return mapValues[coord.y * size.x + coord.x];
}


void Map::setValue(Vector2i coord, int value)
{
	mapValues[coord.y * size.x + coord.x] = value;
}


bool Map::isWithinMap(Vector2i coord) const
{
	return
		coord.x >= 0 &&
		coord.y >= 0 &&
		coord.x < size.x &&
		coord.y < size.y;
}


const Vector2i& Map::getSize() const
{
	return size;
}


void Map::generateObstacles()
{
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			if (rand() % 4 == 0) setValue(Vector2i(x, y), 1);
		}
	}
}
