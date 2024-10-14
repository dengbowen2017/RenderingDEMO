#include "PhysicsSystem.h"

#include "spdlog/spdlog.h"

namespace PhysicsDEMO
{
	PhysicsSystem::PhysicsSystem(const PhysicsSystemConfig& config)
		:m_Gravity(0.0f, -config.Gravity, 0.0f, 0.0f), m_LinearSpeedThreshold(config.LinearSpeedThreshold),
		m_AngularSpeedThreshold(config.AngularSpeedThreshold), m_SleepThreshold(config.SleepThreshold)
	{
	}

	void PhysicsSystem::AddRigidActor(RigidActor* rigid_actor)
	{
		RigidDynamic* dynamic_actor = rigid_actor->is<RigidDynamic>();
		if (dynamic_actor)
		{
			m_RigidDynamics.push_back(dynamic_actor);
		}

		RigidStatic* static_actor = rigid_actor->is<RigidStatic>();
		if (static_actor)
		{
			m_RigidStatics.push_back(static_actor);
		}
	}

	void PhysicsSystem::RemoveRigidActor(RigidActor* rigid_actor)
	{
	}

	void PhysicsSystem::AddParticleBuffer(ParticleBuffer* buffer)
	{
		ParticleRigidBuffer* rigid_buffer = dynamic_cast<ParticleRigidBuffer*>(buffer);
		if (rigid_buffer)
		{
			m_RigidBuffers.push_back(rigid_buffer);
		}
	}

	void PhysicsSystem::RemoveParticleBuffer(ParticleBuffer* buffer)
	{
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
		// only used for dynamic collided with static based on force
		for each (RigidDynamic * actor1 in m_RigidDynamics)
		{
			if (!actor1->IsSleep())
			{
				actor1->ApplyGravity(m_Gravity, dt);
				actor1->ApplyDamping();

				for each (RigidStatic* actor2 in m_RigidStatics)
				{
					Collision collision;
					if (m_Solver.DetectCollision(actor1, actor2, collision))
					{
						m_Solver.AddCollision(collision);
					}
				}
				m_Solver.SolveCollision();

				actor1->UpdateTransform(dt);
				CheckSleep(actor1, dt);
			}
		}

		// shape matching for rigid body collided with static
		for each (ParticleRigidBuffer* rigid_buffer in m_RigidBuffers)
		{
			rigid_buffer->PreSolve(m_RigidStatics, m_Gravity, dt);
			rigid_buffer->Solve();
			rigid_buffer->PostSolve(dt);
		}
	}

	void PhysicsSystem::CheckSleep(RigidDynamic* rigid_dynamic, float dt)
	{
		if (GMath::VectorGetX(GMath::VectorMagnitude(rigid_dynamic->GetLinearVelocity())) <= m_LinearSpeedThreshold
			&& GMath::VectorGetX(GMath::VectorMagnitude(rigid_dynamic->GetAngularVelocity())) <= m_AngularSpeedThreshold)
		{
			rigid_dynamic->AccumulateSleepTime(dt, m_SleepThreshold);
		}
	}
}