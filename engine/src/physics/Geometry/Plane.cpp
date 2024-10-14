#include "Plane.h"

namespace PhysicsDEMO
{
	Plane::Plane(const GMath::MVector& position, const GMath::MQuaternion& rotation)
		:m_Point(position), m_Rotation(rotation)
	{
		m_Type = GeometryType::PLANE;
		m_Normal = GMath::VectorNormalize(GMath::RotateMatrix(rotation) * GMath::MVector(0.0f, 1.0f, 0.0f, 0.0f));
	}
}