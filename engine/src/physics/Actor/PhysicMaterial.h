#pragma once

namespace PhysicsDEMO
{
	struct PhysicMaterial
	{
		float DynamicFriction;
		float StaticFriction;
		float Restitution;

		constexpr PhysicMaterial() noexcept : DynamicFriction(0.5f), StaticFriction(0.0f), Restitution(0.5f) {};
		constexpr PhysicMaterial(float dynamic_friction, float static_friction, float restitution) noexcept : DynamicFriction(dynamic_friction), StaticFriction(static_friction), Restitution(restitution) {};
	};
}