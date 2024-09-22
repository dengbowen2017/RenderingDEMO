#pragma once

#include "Actor/RigidDynamic.h"
#include "Actor/RigidStatic.h"
#include "Collision/CollisionSolver.h"

namespace PhysicsDEMO
{
	struct PhysicsSystemConfig
	{
		float Gravity = 9.8f;
		float LinearSpeedThreshold = 0.2f;
		float AngularSpeedThreshold = 0.25f;
		float SleepThreshold = 0.4f;
	};

	class PhysicsSystem
	{
	public:
		PhysicsSystem(const PhysicsSystemConfig& config);

		void AddRigidActor(RigidActor* body);
		void RemoveRigidActor(RigidActor* body);

		void Update(float dt);

	private:
		void Simulate(float dt);

	private:
		std::vector<RigidActor*> m_RigidActors;
		CollisionSolver m_Solver;

		GMath::MVector m_Gravity;

		float m_Accumulator = 0.0f;
		float m_StepSize = 1.0f / 60.0f;

		float m_LinearSpeedThreshold = 0.2f;
		float m_AngularSpeedThreshold = 0.3f;
		float m_SleepThreshold = 0.5f;
	};
}