#include "Pathfinder.h"



Pathfinder::Pathfinder() 
{
}


Pathfinder::~Pathfinder()
{
}


// This is overridden by the classes that inherit from Pathfinder
Path Pathfinder::generatePath(const Map& map, Vector2i start, Vector2i end, MapDisplayer* mapDisplayer)
{
	return Path(start, end);
}