#pragma once

#include "GMath.h"
#include "Geometry.h"

namespace PhysicsDEMO
{
	class Plane : public Geometry
	{
	public:
		Plane(const GMath::MVector& position, const GMath::MQuaternion& rotation);
		~Plane() = default;

		const GMath::MVector& GetPoint() const { return m_Point; }
		const GMath::MVector& GetNormal() const { return m_Normal; }
		const GMath::MQuaternion& GetRotation() const { return m_Rotation; }

	private:
		GMath::MVector m_Point;
		GMath::MVector m_Normal;
		GMath::MQuaternion m_Rotation;
	};
}