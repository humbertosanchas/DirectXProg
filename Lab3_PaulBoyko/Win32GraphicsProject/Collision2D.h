#pragma once

#include <d3d11.h>
#include <SimpleMath.h>
using DirectX::SimpleMath::Vector2;

struct Box2D
{	
	Box2D()
	{
		center = Vector2::Zero;
		extents = Vector2::Zero;
	}

	Box2D(Vector2 _center, Vector2 _extents)
	{
		center = _center;
		extents = _extents;
	}

	Vector2 center;
	Vector2 extents;
};

struct Circle
{
	Circle() { center = Vector2::Zero; radius = 0.0f; }
	Circle(Vector2 _center, float _radius)
	{
		center = _center;
		radius = _radius;
	}

	Vector2 center;
	float	radius;
};

class Collision2D
{
	public:
		static bool BoxBoxCheck(Box2D boxA, Box2D boxB);
		static bool BoxCircleCheck(Box2D box, Circle circle);
		static bool CircleCircleCheck(Circle circleA, Circle circleB);
};
