#include "Pathfinder.h"



Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
}


Path Pathfinder::generatePath(const Map& map, Vector2i start, Vector2i end)
{
	return Path(start, end);
}


Path Pathfinder::generateAndDrawPath(const Map& map, Vector2i start, Vector2i end, MapDisplayer& mapDisplayer)
{
	return generatePath(map, start, end);
}

