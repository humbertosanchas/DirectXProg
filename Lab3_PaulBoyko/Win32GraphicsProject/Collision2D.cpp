#pragma once
#include "Collision2D.h"

bool Collision2D::BoxBoxCheck(Box2D boxA, Box2D boxB)
{
	Vector2 distance = boxA.center - boxB.center;
	if (fabsf(distance.x) > (boxA.extents.x + boxB.extents.x))
		return false;
	if (fabsf(distance.y) > (boxA.extents.y + boxB.extents.y))
		return false;

	return true;
}

bool Collision2D::BoxCircleCheck(Box2D box, Circle circle)
{
	Vector2 distance = circle.center - box.center;

	if (fabsf(distance.x) > box.extents.x + circle.radius)
	{
		return false;
	}
	if (fabsf(distance.y) > box.extents.y + circle.radius)
	{
		return false;
	}
	if (distance.Length() > (box.extents.Length() + circle.radius))
	{
		return false;
	}

	return true;
}

bool Collision2D::CircleCircleCheck(Circle circleA, Circle circleB)
{
	float distance = Vector2::Distance(circleA.center, circleB.center);
	return distance <= (circleA.radius + circleB.radius);
}