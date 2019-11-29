#include "Vector2i.h"


Vector2i::Vector2i(int _x, int _y) : x(_x), y(_y)
{
}


Vector2i::~Vector2i()
{
}


bool Vector2i::operator==(const Vector2i& rhs) const
{
	return x == rhs.x && y == rhs.y;
}


bool Vector2i::operator!=(const Vector2i& rhs) const
{
	return x != rhs.x || y != rhs.y;
}


Vector2i& Vector2i::operator+=(const Vector2i& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}


Vector2i& Vector2i::operator-=(const Vector2i& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}


Vector2i operator+(Vector2i lhs, const Vector2i& rhs)
{
	return lhs += rhs;
}


Vector2i operator-(Vector2i lhs, const Vector2i& rhs)
{
	return lhs -= rhs;
}