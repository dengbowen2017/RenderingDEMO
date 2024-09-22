#pragma once

#include "RigidActor.h"
#include "RigidCore.h"

namespace PhysicsDEMO
{
	class RigidBody : public RigidActor
	{
	public:
		virtual ~RigidBody() = default;

		virtual void SetGlobalTranslation(const GMath::MVector& translation) override { m_Core.Translation = translation; }
		virtual const GMath::MVector& GetGlobalTranslation() const override { return m_Core.Translation; }
		virtual void SetGlobalRotation(const GMath::MQuaternion& rotation) override { m_Core.Rotation = rotation; }
		virtual const GMath::MQuaternion& GetGlobalRotation() const override { return m_Core.Rotation; }
		virtual GMath::Matrix4x4 GetModelMatrix() const override;

		GMath::MVector GetRefCenterOfMass() const;

		void SetMass(float mass) { m_Core.Mass = mass; m_Core.InvMass = 1.0f / mass; }
		float GetMass() const { return m_Core.Mass; }
		float GetInvMass() const { return m_Core.InvMass; }

		GMath::MMatrix GetRefInertia() const { return m_Core.Inertia; }
		GMath::MMatrix GetRefInvInertia() const { return m_Core.InvInertia; }

		void SetLinearDamping(float damping) { m_Core.LinearDamping = damping; }
		void SetAngularDamping(float damping) { m_Core.AngularDamping = damping; }

		void SetLinearVelocity(const GMath::MVector& velocity) { m_Core.LinearVelocity = velocity; }
		const GMath::MVector& GetLinearVelocity() const { return m_Core.LinearVelocity; }
		void SetAngularVelocity(const GMath::MVector& velocity) { m_Core.AngularVeloctiy = velocity; }
		const GMath::MVector& GetAngularVelocity() const { return m_Core.AngularVeloctiy; }

		void SetMassAndInertia(float mass, const GMath::MMatrix& inertia);
		
		void ApplyGravity(const GMath::MVector& gravity, float dt);
		void ApplyDamping();
		void ApplyLinearImpulse(const GMath::MVector& impulse);
		void ApplyAngularImpulse(const GMath::MVector& impulse);
		
		void UpdateTransform(float dt);

	protected:
		RigidBodyCore m_Core;
	};
}