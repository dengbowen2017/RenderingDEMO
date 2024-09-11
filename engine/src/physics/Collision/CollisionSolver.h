#pragma once

#include "CollisionDefinition.h"

namespace PhysicsDEMO
{
	class CollisionSolver
	{
	public:
		void ImpulseSolver(const Collision& collision);
	};
}