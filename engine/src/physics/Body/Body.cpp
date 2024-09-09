#include "Body.h"

namespace PhysicsDEMO
{
	void Body::SetPhysicMaterial(float friction, float restitution, float damping)
	{
		m_PhysicMaterial.Damping = damping;
		m_PhysicMaterial.Restitution = restitution;
		m_PhysicMaterial.Friction = friction;
	}

	void Body::SetMotionProperty(const GMath::MVector& linear_velocity, const GMath::MVector& angular_velocity)
	{
		m_MotionProperty.LinearVelocity = linear_velocity;
		m_MotionProperty.AngularVelocity = angular_velocity;
	}

	void Body::SetShapeAndMass(std::shared_ptr<Shape> shape, float mass)
	{
		m_Shape = shape;
		m_MassProperty = m_Shape->GetMassProperty(mass);
	}

	GMath::Matrix4x4 Body::GetTransformMatrix() const
	{
		GMath::Matrix4x4 mat;
		GMath::StoreMatrix4x4(&mat, GMath::ModelMatrix(m_Translation, m_Rotation, GMath::MVector(1.0f)));
		return mat;
	}

	void Body::ApplyGravity(float dt)
	{
		m_MotionProperty.LinearVelocity += gravity * dt;
	}

	void Body::ApplyDamping()
	{
		m_MotionProperty.LinearVelocity *= m_PhysicMaterial.Damping;
		m_MotionProperty.AngularVelocity *= m_PhysicMaterial.Damping;
	}

	void Body::ApplyImpluse(const GMath::MVector& impluse)
	{
	}

	void Body::UpdateTransform(float dt)
	{
		m_Translation += m_MotionProperty.LinearVelocity * dt;
		//m_Rotation += m_MotionProperty.AngularVelocity * dt * 0.5 * m_Rotation;
	}
}