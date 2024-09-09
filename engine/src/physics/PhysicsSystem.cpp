#include "PhysicsSystem.h"

namespace PhysicsDEMO
{
	void PhysicsSystem::Initialize(PhysicsSystemType type)
	{
		m_Type = type;
	}

	void PhysicsSystem::AddBody(Body* body)
	{
		m_Bodies.push_back(body);
	}

	void PhysicsSystem::RemoveBody(Body* body)
	{
		auto it = std::find(m_Bodies.begin(), m_Bodies.end(), body);
		if (it != m_Bodies.end())
		{
			m_Bodies.erase(it);
		}
	}

	void PhysicsSystem::Update(float dt)
	{
		for each (Body* body in m_Bodies)
		{
			body->ApplyGravity(dt);
			body->UpdateTransform(dt);
		}
	}
}