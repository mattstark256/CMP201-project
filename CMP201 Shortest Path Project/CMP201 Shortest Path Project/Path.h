#pragma once

#include "Vector2i.h"
#include <vector>


class Path
{
public:
	Path(Vector2i _start, Vector2i _end);
	~Path();

	Vector2i getStart() const { return start; }
	Vector2i getEnd() const { return end; }
	bool isConnected() const { return connected; }
	void setConnected(bool _connected) { connected = _connected; }
	void addPathCoord(Vector2i pathCoord);
	bool contains(Vector2i coord) const;

private:
	Vector2i start;
	Vector2i end;
	bool connected = false;
	std::vector<Vector2i> pathCoords;
};

