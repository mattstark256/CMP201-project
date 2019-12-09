#pragma once


// Vector2i is a 2D integer vector with x and y components


struct Vector2i
{
	int x;
	int y;

	Vector2i(int _x = 0, int _y = 0);
	~Vector2i();

	bool operator==(const Vector2i& rhs) const;
	bool operator!=(const Vector2i& rhs) const;
	Vector2i& operator+=(const Vector2i& rhs);
	Vector2i& operator-=(const Vector2i& rhs);
};


Vector2i operator+(Vector2i lhs, const Vector2i& rhs);
Vector2i operator-(Vector2i lhs, const Vector2i& rhs);
