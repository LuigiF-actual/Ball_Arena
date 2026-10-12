#pragma once

#include <raylib.h>

class Box
{
public:
	Box() = default;

	Box(Vector2 pos, Vector2 size)
		:
		Body({ pos.x, pos.y, size.x, size.y })
	{}

	Box(Rectangle rec)
		:
		Body(rec)
	{}

	float getRight() const
	{
		return Body.x + Body.width;
	}

	float getBottom() const
	{
		return Body.y + Body.height;
	}

	Vector2 getTopLeft() const
	{
		return Vector2{ Body.x,Body.y };
	}

	Vector2 getCenter() const
	{
		return Vector2(Body.x + Body.width / 2, Body.y + Body.height / 2);
	}

	Vector2 getSize() const
	{
		return Vector2(Body.width, Body.height);
	}

	bool contains(const Box& box) const
	{
		return (Body.x <= box.Body.x) && (box.getRight() <= getRight()) && (Body.y <= box.Body.y) && (box.getBottom() <= getBottom());
	}

	bool overlap(const Box& box) const
	{
		return !(Body.x >= box.getRight() || getRight() <= box.Body.x || Body.y >= box.getBottom() || getBottom() <= box.Body.y);
	}

	Rectangle Body = { 0.0f,0.0f,10.0f,10.0f };
	Color BoxColor = PINK;

};
