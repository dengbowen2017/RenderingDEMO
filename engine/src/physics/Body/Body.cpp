#include "Body.h"

namespace PhysicsDEMO
{
	void Body::SetPhysicMaterial(float friction, float restitution, float damping)
	{
		m_PhysicMaterial.Damping = damping;
		m_PhysicMaterial.Restitution = restitution;
		m_PhysicMaterial.Friction = friction;
	}

	void Body::SetLinearVelocity(const GMath::MVector& linear_velocity)
	{
		m_MotionProperty.LinearVelocity = linear_velocity;
	}

	void Body::SetAngularVelocity(const GMath::MVector& angular_velocity)
	{
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
		m_MotionProperty.LinearVelocity += m_MassProperty.InvMass * impluse;
	}

	void Body::ApplyTorque(const GMath::MVector& torque)
	{
		GMath::MMatrix R = GMath::QuaternionToMatrix(m_Rotation);
		m_MotionProperty.AngularVelocity += R * m_MassProperty.InvInertia * GMath::MatrixTranspose(R) * torque;
	}

	void Body::UpdateTransform(float dt)
	{
		m_Translation += m_MotionProperty.LinearVelocity * dt;

		GMath::MQuaternion temp(m_MotionProperty.AngularVelocity);
		m_Rotation += 0.5 * dt * temp * m_Rotation;
		m_Rotation = GMath::QuaternionNormalize(m_Rotation);
	}
}