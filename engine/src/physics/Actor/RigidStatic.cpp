#include "RigidStatic.h"

namespace PhysicsDEMO
{
	RigidStatic::RigidStatic(const GMath::MVector& position, const GMath::MQuaternion& rotation)
	{
		m_Core.Translation = position;
		m_Core.Rotation = rotation;
	}

	GMath::Matrix4x4 RigidStatic::GetModelMatrix() const
	{
		GMath::Matrix4x4 mat;
		GMath::StoreMatrix4x4(&mat, GMath::ModelMatrix(m_Core.Translation, m_Core.Rotation, GMath::MVector(1.0f)));
		return mat;
	}
}