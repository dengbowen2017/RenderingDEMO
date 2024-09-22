#pragma once

#include "RigidActor.h"
#include "RigidCore.h"

namespace PhysicsDEMO
{
	class RigidStatic : public RigidActor
	{
	public:
		RigidStatic(const GMath::MVector& position, const GMath::MQuaternion& rotation);
		~RigidStatic() = default;

		virtual void SetGlobalTranslation(const GMath::MVector& translation) override { m_Core.Translation = translation; }
		virtual const GMath::MVector& GetGlobalTranslation() const override { return m_Core.Translation; }
		virtual void SetGlobalRotation(const GMath::MQuaternion& rotation) override { m_Core.Rotation = rotation; }
		virtual const GMath::MQuaternion& GetGlobalRotation() const override { return m_Core.Rotation; }
		virtual GMath::Matrix4x4 GetModelMatrix() const;

	private:
		RigidActorCore m_Core;
	};

}