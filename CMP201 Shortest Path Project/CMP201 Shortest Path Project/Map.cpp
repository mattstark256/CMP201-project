#include "Map.h"

#include <stdlib.h>     /* srand, rand */


Map::Map(Vector2i _size) : size(_size)
{
	// Initialize the mapValues array
	mapValues = new int[size.x * size.y]{};
}


Map::~Map()
{
	// Delete the mapValues array
	delete[] mapValues;
}


// Return the value stored at a specified map coordinate
int Map::getValue(Vector2i coord) const
{
	return mapValues[coord.y * size.x + coord.x];
}


// Store a value at a specified map coordinate
void Map::setValue(Vector2i coord, int value)
{
	mapValues[coord.y * size.x + coord.x] = value;
}


// Check if a coordinate is within the bounds of the map, and therefore whether getValue and setValue can be used
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


// Randomly place obstacles in some of the tiles
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
