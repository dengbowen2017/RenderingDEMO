#pragma once

#include "Body/Body.h"

namespace PhysicsDEMO
{
	enum PhysicsSystemType
	{
		Default, PBD
	};

	class PhysicsSystem
	{
	public:
		~PhysicsSystem() = default;

		void Initialize(PhysicsSystemType type);

		void AddBody(Body* body);
		void RemoveBody(Body* body);

		void Update(float dt);

	private:
		PhysicsSystemType m_Type;
		std::vector<Body*> m_Bodies;
	};
}