#pragma once

#include <raylib.h>

#include "Box.hpp"



class KinectBody
{
public:
	KinectBody() = default;
	KinectBody(float mass_)
		:
		mass(mass_)
	{}


	Vector2 velocity = { 0.0f };
	Vector2 direction = { 0.0f };
	float acceleration = { 0.0f };
	float mass;
	float totalForce;
	float speed = 0.0f;
	bool isMoving = false;

};