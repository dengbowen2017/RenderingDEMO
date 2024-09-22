#pragma once

#include "RigidBody.h"
#include "RigidCore.h"

namespace PhysicsDEMO
{
	class RigidDynamic : public RigidBody
	{
	public:
		RigidDynamic(const GMath::MVector& position, const GMath::MQuaternion& rotation);
		~RigidDynamic() = default;

		bool IsSleep() const { return m_IsSleep; }
		void AccumulateSleepTime(float dt, float threshold);

	private:
		bool m_IsSleep;
		float m_SleepTimer;
	};
}