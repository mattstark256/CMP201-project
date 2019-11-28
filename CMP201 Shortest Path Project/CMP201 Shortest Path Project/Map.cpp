#include "Map.h"



Map::Map(Vector2i _size) : size(_size)
{
	mapValues = new int[size.x * size.y];
}


Map::~Map()
{
	delete mapValues;
}


int Map::getValue(const Vector2i& coord)
{
	return mapValues[coord.y * size.x + coord.x];
}


void Map::setValue(const Vector2i& coord, int value)
{
	mapValues[coord.y * size.x + coord.x] = value;
}


bool Map::isWithinMap(const Vector2i& coord)
{
	return
		coord.x >= 0 &&
		coord.y >= 0 &&
		coord.x < size.x &&
		coord.y < size.y;
}
