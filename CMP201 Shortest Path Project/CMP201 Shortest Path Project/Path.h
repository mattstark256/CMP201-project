#pragma once

#include "Vector2i.h"
#include <vector>


// Path contains a start and end point and can also contain a sequence of coordinates connecting the two.


class Path
{
public:
	Path(Vector2i _start, Vector2i _end);
	~Path();

	Vector2i getStart() const { return start; }
	Vector2i getEnd() const { return end; }
	const std::vector<Vector2i>* getPathCoords() const { return &pathCoords; }
	bool isConnected() const { return connected; }
	void setConnected(bool _connected) { connected = _connected; }
	void addPathCoord(Vector2i pathCoord);
	bool contains(Vector2i coord) const;

private:
	Vector2i start;
	Vector2i end;
	std::vector<Vector2i> pathCoords;
	bool connected = false; // Whether a route exists between the start and end points
};

