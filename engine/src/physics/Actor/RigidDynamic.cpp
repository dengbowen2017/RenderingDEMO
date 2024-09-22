#include "RigidDynamic.h"

namespace PhysicsDEMO
{
	RigidDynamic::RigidDynamic(const GMath::MVector& position, const GMath::MQuaternion& rotation)
		:m_SleepTimer(0.0f), m_IsSleep(false)
	{
		m_Core.Translation = position;
		m_Core.Rotation = rotation;
		m_Core.LinearVelocity = GMath::MVector(0.0f);
		m_Core.AngularVeloctiy = GMath::MVector(0.0f);
		m_Core.LinearDamping = 0.999f;
		m_Core.AngularDamping = 0.98f;
	}

	void RigidDynamic::AccumulateSleepTime(float dt, float threshold)
	{
		m_SleepTimer += dt;
		m_IsSleep = m_SleepTimer > threshold;
	}
}