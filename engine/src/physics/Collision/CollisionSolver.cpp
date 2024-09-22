#include "CollisionSolver.h"

#include "physics/Geometry/ConvexHull.h"
#include "physics/Geometry/Plane.h"

namespace PhysicsDEMO
{
	bool CollisionSolver::DetectCollision(RigidActor* actor1, RigidActor* actor2, Collision& collision)
	{
		RigidDynamic* dynamic_actor2 = actor2->is<RigidDynamic>();
		if (dynamic_actor2)
		{
			//TODO: deal with dynamic

		}

		RigidStatic* static_actor2 = actor2->is<RigidStatic>();
		if (static_actor2)
		{
			RigidActorPair pair;
			pair.Actor1 = actor1;
			pair.Actor2 = actor2;

			// temp
			if (actor1->GetShape()->GetGeometry()->GetType() == GeometryType::CONVEXHULL && actor2->GetShape()->GetGeometry()->GetType() == GeometryType::PLANE)
			{
				pair.Type = CollisionType::CONVEXHULL_PLANE;
			}

			return DynamicWithStatic(pair, collision);
		}
	}

	void CollisionSolver::AddCollision(const Collision& collision)
	{
		m_Collisions.push_back(collision);
	}

	void CollisionSolver::SolveCollision()
	{
		for each (const Collision& collision in m_Collisions)
		{
			ImpulseSolver(collision);
		}

		m_Collisions.clear();
	}

	bool CollisionSolver::DynamicWithStatic(const RigidActorPair& pair, Collision& collision)
	{
		RigidDynamic* actor1 = (RigidDynamic*)(pair.Actor1);
		RigidStatic* actor2 = (RigidStatic*)(pair.Actor2);

		switch (pair.Type)
		{
		case CollisionType::CONVEXHULL_PLANE:
			ConvexHull* actor1_geo = (ConvexHull*)(actor1->GetShape()->GetGeometry().get());
			Plane* actor2_geo = (Plane*)(actor2->GetShape()->GetGeometry().get());

			const std::vector<GMath::Vector3>& vertices = actor1_geo->GetVertices();
			const std::vector<GMath::MVector>& pos_vecs = actor1_geo->GetPositionVectors();

			GMath::MMatrix R = GMath::RotateMatrix(actor1->GetGlobalRotation());
			GMath::MVector average_position(0.0f);
			GMath::MVector average_velocity(0.0f);

			int n = 0;
			for (size_t i = 0; i < vertices.size(); i++)
			{
				GMath::MVector new_pos = GMath::LoadVector3(&vertices[i]);
				new_pos = R * new_pos + actor1->GetGlobalTranslation();

				if (GMath::VectorGetX(GMath::VectorDot(new_pos - actor2_geo->GetPoint(), actor2_geo->GetNormal())) < 0)
				{
					GMath::MVector velocity = actor1->GetLinearVelocity() + GMath::VectorCross(actor1->GetAngularVelocity(), R * pos_vecs[i]);

					average_position += new_pos;
					average_velocity += velocity;
					n++;
				}
			}

			if (n != 0 && GMath::VectorGetX(GMath::VectorDot(average_velocity, actor2_geo->GetNormal())) < 0)
			{
				collision.Actor1 = pair.Actor1;
				collision.Actor2 = pair.Actor2;
				collision.Point = average_position / n;
				collision.Velocity = average_velocity / n;
				collision.Normal = actor2_geo->GetNormal();
				return true;
			}
		}

		return false;
	}

	void CollisionSolver::ImpulseSolver(const Collision& collision)
	{
		RigidDynamic* actor1 = (RigidDynamic*)(collision.Actor1);

		GMath::MVector v_n = GMath::VectorDot(collision.Normal, collision.Velocity) * collision.Normal;
		GMath::MVector v_t = collision.Velocity - v_n;

		std::shared_ptr<PhysicMaterial> material = actor1->GetShape()->GetMaterial();
		float a = 1 - material->DynamicFriction * (1 + material->Restitution) * GMath::VectorGetX(GMath::VectorMagnitude(v_n)) / GMath::VectorGetX(GMath::VectorMagnitude(v_t));
		a = a > material->StaticFriction ? a : material->StaticFriction;

		v_n *= -material->Restitution;
		v_t *= a;

		GMath::MVector now_center_of_mass = actor1->GetRefCenterOfMass() + actor1->GetGlobalTranslation();
		GMath::MMatrix R = GMath::QuaternionToMatrix(actor1->GetGlobalRotation());
		GMath::MMatrix cross_mat = GMath::VectorCrossToMatrix(collision.Point - now_center_of_mass);
		GMath::MMatrix K = actor1->GetInvMass() * GMath::MMatrix::Identity() - cross_mat * R * actor1->GetRefInvInertia() * GMath::MatrixTranspose(R) * cross_mat;
		K.r[3] = GMath::g_MatIdentityR3;

		GMath::MMatrix K_inv = GMath::MatrixInverse(K);
		GMath::MVector vec = v_t + v_n - collision.Velocity;

		GMath::MVector impulse = K_inv * vec;
		GMath::MVector torque = cross_mat * impulse;

		actor1->ApplyLinearImpulse(impulse);
		actor1->ApplyAngularImpulse(torque);
	}
}


