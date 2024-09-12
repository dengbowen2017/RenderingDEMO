#include "PhysicsSystem.h"

#include "spdlog/spdlog.h"

namespace PhysicsDEMO
{
	void PhysicsSystem::Initialize(PhysicsSystemType type)
	{
		m_Type = type;

		plane1.Normal = GMath::MVector(0.0f, 1.0f, 0.0f, 0.0f);
		plane1.Point = GMath::MVector(0.0f);

		plane2.Normal = GMath::MVector(1.0f, 0.0f, 0.0f, 0.0f);
		plane2.Point = GMath::MVector(-2.0f, 0.0f, 0.0f, 0.0f);
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
		m_Accumulator += dt;
		if (m_Accumulator < m_StepSize)
		{
			return;
		}
		m_Accumulator -= m_StepSize;
		Simulate(m_StepSize);
	}

	void PhysicsSystem::Simulate(float dt)
	{
		Collision collision;

		for each (Body * body in m_Bodies)
		{
			body->ApplyGravity(dt);
			body->ApplyDamping();

			if (isCollided(body, plane1, collision))
			{
				m_Solver.ImpulseSolver(collision);
			}

			if (isCollided(body, plane2, collision))
			{
				m_Solver.ImpulseSolver(collision);
			}

			body->UpdateTransform(dt);
		}
	}

	bool PhysicsSystem::isCollided(Body* body, const PlaneCollider& collider, Collision& collision)
	{
		GMath::MMatrix R = GMath::RotateMatrix(body->m_Rotation);
		GMath::MVector average_position(0.0f);
		GMath::MVector average_velocity(0.0f);

		int n = 0;

		const std::vector<GMath::Vector3>& vertices = body->m_Shape->GetVertices();
		const std::vector<GMath::MVector>& pos_vecs = body->m_Shape->GetPositionVectors();

		for (size_t i = 0; i < vertices.size(); i++)
		{
			GMath::MVector new_pos = GMath::LoadVector3(&vertices[i]);
			new_pos = R * new_pos + body->m_Translation;

			if (GMath::VectorGetX(GMath::VectorDot(new_pos - collider.Point, collider.Normal)) < 0)
			{
				GMath::MVector velocity = body->m_MotionProperty.LinearVelocity + GMath::VectorCross(body->m_MotionProperty.AngularVelocity, R * pos_vecs[i]);

				average_position += new_pos;
				average_velocity += velocity;
				n++;
			}
		}

		if (n != 0 && GMath::VectorGetX(GMath::VectorDot(average_velocity, collider.Normal)) < 0)
		{
			collision.ActiveBody = body;
			collision.Plane = collider;
			collision.Point = average_position / n;
			collision.Velocity = average_velocity / n;
			return true;
		}

		return false;
	}
}