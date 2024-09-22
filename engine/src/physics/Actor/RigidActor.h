#pragma once

#include "GMath.h"
#include "Shape.h"

namespace PhysicsDEMO
{
	class RigidActor
	{
	public:
		virtual ~RigidActor() = default;

		template<typename T>
		T* is() { return dynamic_cast<T*>(this); }
		
		const std::shared_ptr<Shape>& GetShape() const { return m_Shape; }
		void DetachShape() { m_Shape.reset(); }
		void AttachShape(std::shared_ptr<Shape> shape) { m_Shape = shape; }

		virtual void SetGlobalTranslation(const GMath::MVector& translation) = 0;
		virtual const GMath::MVector& GetGlobalTranslation() const = 0;

		virtual void SetGlobalRotation(const GMath::MQuaternion& rotation) = 0;
		virtual const GMath::MQuaternion& GetGlobalRotation() const = 0;

		virtual GMath::Matrix4x4 GetModelMatrix() const = 0;

	protected:
		std::shared_ptr<Shape> m_Shape;
	};
}