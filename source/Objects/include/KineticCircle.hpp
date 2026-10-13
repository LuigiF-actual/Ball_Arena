#pragma once

#include <raylib.h>

#include "Box.hpp"


class KineticCircle
{

public:
	KineticCircle() = default;
	KineticCircle(float radius_,Vector2 pos_, Color color_) 
		:
		m_Radius(radius_),
		m_Pos(pos_),
		m_Color(color_)
	{}

	~KineticCircle() = default;

	const Vector2& getPos() const
	{
		return m_Pos;
	}

	const float& getRadius() const
	{
		return m_Radius;
	}

	const Color& getColor() const
	{
		return m_Color;
	}

	Box getCollisionBox() const
	{
		return 
		{
			m_Pos.x - m_Radius,
			m_Pos.y - m_Radius,
			m_Radius * 2.0f,
			m_Radius * 2.0f
		};
	}

	bool contain(const KineticCircle& other_) const
	{
		return Vector2Distance(m_Pos, other_.getPos()) + other_.getRadius() <= m_Radius;
	}

	bool overlap(const KineticCircle& other_) const
	{
		return CheckCollisionCircles(m_Pos, m_Radius, other_.getPos(), other_.getRadius());
	}

private:


	float m_Radius = 0.0f;
	Vector2 m_Pos{0.0f};
	Color m_Color{RED};
	//Rectangle m_CollisionBox{0.0f};

};
