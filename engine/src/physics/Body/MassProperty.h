#pragma once

#include "GMath.h"

namespace PhysicsDEMO
{
	struct MassProperty
	{
		GMath::MMatrix Inertia;
		GMath::MMatrix InvInertia;
		float Mass;
		float InvMass;
	};
}