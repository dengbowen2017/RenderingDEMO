#pragma once

#include "GMath.h"
#include "physics/Actor/RigidStatic.h"
#include "physics/Geometry/Plane.h"

namespace PhysicsDEMO
{
	class ParticleBuffer
	{
	public:
		ParticleBuffer(const std::vector<GMath::MVector>& positions, const std::vector<GMath::MVector>& velocities)
			:m_ParticlePositions(positions), m_ParticleVelocities(velocities)
		{}
		virtual ~ParticleBuffer() = default;

		const std::vector<GMath::MVector>& GetPositions() { return m_ParticlePositions; }
		void SetPositions(const std::vector<GMath::MVector> positions) { m_ParticlePositions = positions; }

		const std::vector<GMath::MVector>& GetVelocities() { return m_ParticleVelocities; }
		void SetVelocities(const std::vector<GMath::MVector> velocities) { m_ParticleVelocities = velocities; }

	protected:
		std::vector<GMath::MVector> m_ParticlePositions;
		std::vector<GMath::MVector> m_ParticleVelocities;
	};

	class ParticleRigidBuffer : public ParticleBuffer
	{
	public:
		ParticleRigidBuffer(const std::vector<GMath::MVector>& positions, const std::vector<GMath::MVector>& velocities, const GMath::MVector& translation);

		GMath::MVector GetTranslation() const { return m_Translation; }
		GMath::MMatrix GetRotation() const { return m_Rotation; }
		GMath::Matrix4x4 GetModelMatrix() const;

		void PreSolve(const std::vector<RigidStatic*>& rigid_statics, const GMath::MVector& gravity, float dt);
		void Solve();
		void PostSolve(float dt);

	private:
		GMath::MVector CalculateCenterOfMass();

	private:
		// pre-calculate
		std::vector<GMath::MVector> m_PositionVectors;
		GMath::MVector m_OriginalCenterOfMass;
		GMath::MVector m_OriginalTranslation;
		GMath::MMatrix m_InverseRRt;

		//only used to store old position and update the velocity
		GMath::MVector m_NewCenterOfMass;
		std::vector<Plane*> m_Collisions;
		std::vector<GMath::MVector> m_ParticleOldPositions; 

		//integration
		GMath::MMatrix m_Rotation;
		GMath::MVector m_Translation;
	};
}