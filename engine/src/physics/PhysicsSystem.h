#pragma once

#include "Actor/RigidDynamic.h"
#include "Actor/RigidStatic.h"
#include "Collision/CollisionSolver.h"
#include "PBD/ParticleBuffer.h"

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

		void AddRigidActor(RigidActor* rigid_actor);
		void RemoveRigidActor(RigidActor* rigid_actor);

		// TODO: separate PBD from the CPU simulator and build a GPU particle simulator
		void AddParticleBuffer(ParticleBuffer* buffer);
		void RemoveParticleBuffer(ParticleBuffer* buffer);

		void Update(float dt);

	private:
		void Simulate(float dt);
		void CheckSleep(RigidDynamic* rigid_dynamic, float dt);

	private:
		std::vector<RigidStatic*> m_RigidStatics;
		std::vector<RigidDynamic*> m_RigidDynamics;

		std::vector<ParticleRigidBuffer*> m_RigidBuffers;

		CollisionSolver m_Solver;

		float m_Accumulator = 0.0f;
		float m_StepSize = 1.0f / 60.0f;

		GMath::MVector m_Gravity;
		float m_LinearSpeedThreshold = 0.2f;
		float m_AngularSpeedThreshold = 0.3f;
		float m_SleepThreshold = 0.5f;
	};
}