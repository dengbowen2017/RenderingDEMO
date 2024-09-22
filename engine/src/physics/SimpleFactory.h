#pragma once

#include "physics/Actor/RigidDynamic.h"
#include "physics/Actor/RigidStatic.h"

namespace PhysicsDEMO
{
	class SimpleFactory
	{
	public:
		static std::shared_ptr<RigidDynamic> CreateRigidDynamic(const GMath::MVector& position, const GMath::MQuaternion& rotation, float mass, std::shared_ptr<Geometry> geo, std::shared_ptr<PhysicMaterial> material);
		static std::shared_ptr<RigidStatic> CreateRigidStatic(const GMath::MVector& position, const GMath::MQuaternion& rotation, std::shared_ptr<Geometry> geo, std::shared_ptr<PhysicMaterial> material);
	};
}