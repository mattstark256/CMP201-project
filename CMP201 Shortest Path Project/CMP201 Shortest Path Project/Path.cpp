#include "Path.h"

#include <algorithm> // find



Path::Path(Vector2i _start, Vector2i _end) : start(_start), end(_end)
{
}


Path::~Path()
{
}


void Path::addPathCoord(Vector2i pathCoord)
{
	pathCoords.push_back(pathCoord);
}


bool Path::contains(Vector2i coord)const
{
	return std::find(pathCoords.begin(), pathCoords.end(), coord) != pathCoords.end();
}
