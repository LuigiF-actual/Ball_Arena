#pragma once

#include <raylib.h>
#include <cmath>

#include "Box.hpp"
#include "WorldConfig.hpp"



class KineticBody
{
public:
	KineticBody() = default;
	KineticBody(float mass_)
		:
		mass(mass_)
	{}

	void move(Vector2& pos_)
	{
		const float gft = GetFrameTime();

		velocity = Vector2Add(velocity,Vector2Scale(direction, gft));
		speed = Vector2Length(velocity);

		const float newSpeed = std::max(0.0f, speed - config::friction * gft);

		if (speed > 0.0f)
		{
			velocity = Vector2Scale(velocity, newSpeed / speed);
		}

		pos_ = Vector2Add(pos_, Vector2Scale(velocity, gft));
		speed = newSpeed;

	}

	Vector2 velocity = { 0.0f,0.0f };
	Vector2 direction = { 0.0f,0.0f };
	float acceleration{ 0.0f };
	float mass;
	float totalForce;
	float speed = 0.0f;
	bool isMoving = false;

};