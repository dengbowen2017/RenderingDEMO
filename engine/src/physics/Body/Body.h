#pragma once

#include "physics/Shape/Shape.h"
#include "MassProperty.h"
#include "MotionProperty.h"
#include "PhysicMaterial.h"

namespace PhysicsDEMO
{
	class Body
	{
	public:
		Body() : m_Translation(0.0f), m_Rotation(0.0f, 0.0f, 0.0f, 1.0f), gravity(0.0f, -9.8f, 0.0f, 0.0f) {}
		~Body() = default;

		void SetTranslation(const GMath::MVector& translation) { m_Translation = translation; }
		void SetRotation(const GMath::MQuaternion& rotation) { m_Rotation = rotation; }

		void SetPhysicMaterial(float friction, float restitution, float damping);
		void SetLinearVelocity(const GMath::MVector& linear_velocity);
		void SetAngularVelocity(const GMath::MVector& angular_velocity);
		void SetShapeAndMass(std::shared_ptr<Shape> shape, float mass);

		GMath::Matrix4x4 GetTransformMatrix() const;

		void ApplyGravity(float dt);
		void ApplyDamping();
		void ApplyImpluse(const GMath::MVector& impluse);
		void ApplyTorque(const GMath::MVector& torque);
		
		void UpdateTransform(float dt);

	private:
		friend class PhysicsSystem;
		friend class CollisionSolver;

		GMath::MVector m_Translation;
		GMath::MQuaternion m_Rotation;

		std::shared_ptr<Shape> m_Shape;
		PhysicMaterial m_PhysicMaterial = {};

		MassProperty m_MassProperty = {};
		MotionProperty m_MotionProperty = {};

		// temp
		GMath::MVector gravity;
	};
}