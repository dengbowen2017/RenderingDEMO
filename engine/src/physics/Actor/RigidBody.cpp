#include "RigidBody.h"

#include "physics/Geometry/ConvexHull.h"

namespace PhysicsDEMO
{
	GMath::Matrix4x4 RigidBody::GetModelMatrix() const
	{
		GMath::Matrix4x4 mat;
		GMath::StoreMatrix4x4(&mat, GMath::ModelMatrix(m_Core.Translation, m_Core.Rotation, GMath::MVector(1.0f)));
		return mat;
	}

	GMath::MVector RigidBody::GetRefCenterOfMass() const
	{
		std::shared_ptr<Geometry> geo = m_Shape->GetGeometry();

		switch (geo->GetType())
		{
		case GeometryType::CONVEXHULL:
			ConvexHull* convex_hull = (ConvexHull*)(geo.get());
			return convex_hull->GetCenterOfMass();
		}
	}

	void RigidBody::SetMassAndInertia(float mass, const GMath::MMatrix& inertia)
	{
		m_Core.Mass = mass;
		m_Core.InvMass = 1.0f / mass;
		m_Core.Inertia = inertia;
		m_Core.InvInertia = GMath::MatrixInverse(inertia);
	}

	void RigidBody::ApplyGravity(const GMath::MVector& gravity, float dt)
	{
		m_Core.LinearVelocity += gravity * dt;
	}

	void RigidBody::ApplyDamping()
	{
		m_Core.LinearVelocity *= m_Core.LinearDamping;
		m_Core.AngularDamping *= m_Core.AngularDamping;
	}

	void RigidBody::ApplyLinearImpulse(const GMath::MVector& impulse)
	{
		m_Core.LinearVelocity += impulse * m_Core.InvMass;
	}

	void RigidBody::ApplyAngularImpulse(const GMath::MVector& impulse)
	{
		GMath::MMatrix R = GMath::RotateMatrix(m_Core.Rotation);
		m_Core.AngularVeloctiy += R * m_Core.InvInertia * GMath::MatrixTranspose(R) * impulse;
	}

	void RigidBody::UpdateTransform(float dt)
	{
		m_Core.Translation += m_Core.LinearVelocity * dt;
		GMath::MQuaternion w2q(dt * 0.5 * m_Core.AngularVeloctiy);
		m_Core.Rotation += w2q * m_Core.Rotation;
		m_Core.Rotation = GMath::QuaternionNormalize(m_Core.Rotation);
	}
}