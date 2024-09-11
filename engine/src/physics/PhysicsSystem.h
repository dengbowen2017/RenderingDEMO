#pragma once

#include "Body/Body.h"
#include "Collision/CollisionDefinition.h"
#include "Collision/CollisionSolver.h"

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
		void Simulate(float dt);

		// TODO: Add Collision Detector and BodyPair
		bool isCollided(Body* body, const PlaneCollider& collider, Collision& collision);

	private:
		PhysicsSystemType m_Type;
		std::vector<Body*> m_Bodies;
		CollisionSolver m_Solver;

		float m_Accumulator = 0.0f;
		float m_StepSize = 1.0f / 60.0f;

		//Temp
		PlaneCollider plane1;
		PlaneCollider plane2;
	};
}