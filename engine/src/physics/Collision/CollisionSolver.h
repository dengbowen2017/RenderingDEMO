#pragma once

#include "physics/Actor/RigidDynamic.h"
#include "physics/Actor/RigidStatic.h"
#include "GMath.h"

namespace PhysicsDEMO
{
	enum CollisionType
	{
		CONVEXHULL_PLANE
	};

	struct RigidActorPair
	{
		CollisionType Type;
		RigidActor* Actor1;
		RigidActor* Actor2;
	};

	struct Collision
	{
		// collision point
		GMath::MVector Point;
		GMath::MVector Velocity;
		GMath::MVector Normal;
		// actors
		RigidActor* Actor1;
		RigidActor* Actor2;
	};

	class CollisionSolver
	{
	public:
		bool DetectCollision(RigidActor* actor1, RigidActor* actor2, Collision& collision);
		void AddCollision(const Collision& collision);
		void SolveCollision();

	private:
		bool DynamicWithStatic(const RigidActorPair& pair, Collision& collision);
		void ImpulseSolver(const Collision& collision);
	
	private:
		std::vector<Collision> m_Collisions;
	};
}