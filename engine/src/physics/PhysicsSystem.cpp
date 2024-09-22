#include "PhysicsSystem.h"

#include "spdlog/spdlog.h"

namespace PhysicsDEMO
{
	PhysicsSystem::PhysicsSystem(const PhysicsSystemConfig& config)
		:m_Gravity(0.0f, -config.Gravity, 0.0f, 0.0f), m_LinearSpeedThreshold(config.LinearSpeedThreshold),
		m_AngularSpeedThreshold(config.AngularSpeedThreshold), m_SleepThreshold(config.SleepThreshold)
	{
	}

	void PhysicsSystem::AddRigidActor(RigidActor* body)
	{
		m_RigidActors.push_back(body);
	}

	void PhysicsSystem::RemoveRigidActor(RigidActor* body)
	{
		auto it = std::find(m_RigidActors.begin(), m_RigidActors.end(), body);
		if (it != m_RigidActors.end())
		{
			m_RigidActors.erase(it);
		}
	}

	void PhysicsSystem::Update(float dt)
	{
		m_Accumulator += dt;
		if (m_Accumulator >= m_StepSize)
		{
			m_Accumulator -= m_StepSize;
			Simulate(m_StepSize);
		}
	}

	void PhysicsSystem::Simulate(float dt)
	{
		for each (RigidActor * actor1 in m_RigidActors)
		{
			RigidDynamic* dynamic_actor1 = actor1->is<RigidDynamic>();

			if (dynamic_actor1 && dynamic_actor1->IsSleep() == false)
			{
				dynamic_actor1->ApplyGravity(m_Gravity, dt);
				dynamic_actor1->ApplyDamping();

				for each (RigidActor * actor2 in m_RigidActors)
				{
					if (actor1 != actor2)
					{
						Collision collision;
						if (m_Solver.DetectCollision(actor1, actor2, collision))
						{
							m_Solver.AddCollision(collision);
						}
					}
				}

				m_Solver.SolveCollision();
				dynamic_actor1->UpdateTransform(dt);

				if (GMath::VectorGetX(GMath::VectorMagnitude(dynamic_actor1->GetLinearVelocity())) <= m_LinearSpeedThreshold
					&& GMath::VectorGetX(GMath::VectorMagnitude(dynamic_actor1->GetAngularVelocity())) <= m_AngularSpeedThreshold)
				{
					dynamic_actor1->AccumulateSleepTime(dt, m_SleepThreshold);
				}
			}
		}
	}
}