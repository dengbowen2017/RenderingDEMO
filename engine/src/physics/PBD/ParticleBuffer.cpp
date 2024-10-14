#include "ParticleBuffer.h"

namespace PhysicsDEMO
{
	ParticleRigidBuffer::ParticleRigidBuffer(const std::vector<GMath::MVector>& positions, const std::vector<GMath::MVector>& velocities, const GMath::MVector& translation)
		:ParticleBuffer(positions, velocities), m_ParticleOldPositions(positions), m_Collisions(positions.size(), nullptr), m_OriginalTranslation(translation)
	{
		for (size_t i = 0; i < positions.size(); i++)
		{
			m_ParticlePositions[i] += m_OriginalTranslation;
		}

		m_OriginalCenterOfMass = CalculateCenterOfMass();

		m_PositionVectors.reserve(positions.size());
		for each (const GMath::MVector & pos in m_ParticlePositions)
		{
			m_PositionVectors.emplace_back(pos - m_OriginalCenterOfMass);
		}

		m_InverseRRt = GMath::MMatrix::Zero();
		for each (const GMath::MVector & position_vec in m_PositionVectors)
		{
			m_InverseRRt += GMath::VectorDotVectorTranspose(position_vec, position_vec);
		}
		m_InverseRRt.r[3] = GMath::g_MatIdentityR3;

		m_InverseRRt = GMath::MatrixInverse(m_InverseRRt);
	}

	GMath::Matrix4x4 ParticleRigidBuffer::GetModelMatrix() const
	{
		GMath::Matrix4x4 mRes;
		GMath::StoreMatrix4x4(&mRes, GMath::TranslateMatrix(m_Translation) * m_Rotation);
		return mRes;
	}

	void ParticleRigidBuffer::PreSolve(const std::vector<RigidStatic*>& rigid_statics, const GMath::MVector& gravity, float dt)
	{
		for (size_t i = 0; i < m_ParticlePositions.size(); i++)
		{
			m_ParticleVelocities[i] += gravity * dt;
			m_ParticleVelocities[i] *= 0.99f;
			m_ParticleOldPositions[i] = m_ParticlePositions[i];
			m_ParticlePositions[i] += m_ParticleVelocities[i] * dt;
			m_Collisions[i] = nullptr;

			// check detection
			for each (RigidStatic * rigid_static in rigid_statics)
			{
				Plane* plane = (Plane*)rigid_static->GetShape()->GetGeometry().get();
				float temp = GMath::VectorGetX(GMath::VectorDot(m_ParticlePositions[i] - plane->GetPoint(), plane->GetNormal()));
				if (temp < 0)
				{
					m_ParticlePositions[i] -= temp * plane->GetNormal();
					m_Collisions[i] = plane;
				}
			}
		}
	}

	void ParticleRigidBuffer::Solve()
	{
		m_NewCenterOfMass = CalculateCenterOfMass();

		GMath::MMatrix temp = GMath::MMatrix::Zero();
		for (size_t i = 0; i < m_PositionVectors.size(); i++)
		{
			temp += GMath::VectorDotVectorTranspose(m_ParticlePositions[i] - m_NewCenterOfMass, m_PositionVectors[i]);
		}
		temp.r[3] = GMath::g_MatIdentityR3;

		m_Rotation = GMath::PolarDecomposition(temp * m_InverseRRt);
		m_Translation = m_OriginalTranslation + m_NewCenterOfMass - m_OriginalCenterOfMass;
	}

	void ParticleRigidBuffer::PostSolve(float dt)
	{
		for (size_t i = 0; i < m_ParticlePositions.size(); i++)
		{
			m_ParticlePositions[i] = m_Rotation * m_PositionVectors[i] + m_NewCenterOfMass;
			m_ParticleVelocities[i] = (m_ParticlePositions[i] - m_ParticleOldPositions[i]) * (1.0f / dt);

			// update velocities of collided particles
			if (m_Collisions[i] != nullptr)
			{
				GMath::MVector vertical_velocity = GMath::VectorDot(m_ParticleVelocities[i], m_Collisions[i]->GetNormal()) * m_Collisions[i]->GetNormal();
				GMath::MVector horizontal_velocity = m_ParticleVelocities[i] - vertical_velocity;

				vertical_velocity *= -0.5;
				horizontal_velocity *= 0.5;
				m_ParticleVelocities[i] = vertical_velocity + horizontal_velocity;
			}
		}
	}

	GMath::MVector ParticleRigidBuffer::CalculateCenterOfMass()
	{
		GMath::MVector center_of_mass(0.0f);
		for each (const GMath::MVector & pos in m_ParticlePositions)
		{
			center_of_mass += pos;
		}
		center_of_mass /= static_cast<float>(m_ParticlePositions.size());
		return center_of_mass;
	}
}