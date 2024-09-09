#pragma once

namespace PhysicsDEMO
{
	struct PhysicMaterial
	{
		float Damping;
		float Friction;
		float Restitution;

		constexpr PhysicMaterial() noexcept : Damping(0.99f), Friction(0.5f), Restitution(0.5f) {};
		constexpr PhysicMaterial(float damping, float friction, float restitution) noexcept : Damping(damping), Friction(friction), Restitution(restitution) {};
	};
}