#pragma once

#include "GMath.h"

namespace PhysicsDEMO
{
	class Body;

	struct PlaneCollider
	{
		GMath::MVector Normal;
		GMath::MVector Point;
	};

	// only for collision between active object and static plane
	struct Collision
	{
		// active object
		GMath::MVector Point;
		GMath::MVector Velocity;
		Body* ActiveBody;

		// plane
		PlaneCollider Plane;
	};
}