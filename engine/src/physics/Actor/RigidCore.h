#pragma once

#include "GMath.h"

namespace PhysicsDEMO
{
	struct RigidActorCore
	{
		GMath::MVector Translation;
		GMath::MQuaternion Rotation;
	};

	struct RigidBodyCore : public RigidActorCore
	{
		GMath::MVector LinearVelocity;
		GMath::MVector AngularVeloctiy;
		float LinearDamping;
		float AngularDamping;
		float Mass;
		float InvMass;
		GMath::MMatrix Inertia;
		GMath::MMatrix InvInertia;
	};
}