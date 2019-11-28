#pragma once


struct Vector2i
{
	int x;
	int y;

	Vector2i(int _x = 0, int _y = 0);
	~Vector2i();

	bool operator==(const Vector2i& rhs);
	Vector2i& operator+=(const Vector2i& rhs);
	Vector2i& operator-=(const Vector2i& rhs);
};


Vector2i operator+(Vector2i lhs, const Vector2i& rhs);
Vector2i operator-(Vector2i lhs, const Vector2i& rhs);
