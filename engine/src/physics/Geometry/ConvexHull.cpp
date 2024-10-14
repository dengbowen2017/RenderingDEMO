#include "ConvexHull.h"

namespace PhysicsDEMO
{
	ConvexHull::ConvexHull(const std::vector<GMath::Vector3>& vertices)
		:m_Vertices(vertices)
	{
		m_Type = GeometryType::CONVEXHULL;
		CalculateCenterOfMass();
		CalculatePositionVectors();
	}

	GMath::MMatrix ConvexHull::GetInertia(float mass) const
	{
		GMath::MMatrix inertia = GMath::MMatrix::Zero();

		for (size_t i = 0; i < m_PositionVectors.size(); i++)
		{
			inertia += GMath::PartOfInertiaMatrix(m_PositionVectors[i]);
		}

		inertia *= mass / m_PositionVectors.size();
		inertia.r[3] = GMath::g_MatIdentityR3;

		return inertia;
	}

	void ConvexHull::CalculateCenterOfMass()
	{
		GMath::MVector res(0.0f);
		GMath::MVector temp(0.0f);

		for (size_t i = 0; i < m_Vertices.size(); i++)
		{
			temp = GMath::LoadVector3(&m_Vertices[i]);
			res += temp;
		}

		m_Center_Of_Mass = res / static_cast<float>(m_Vertices.size());
	}

	void ConvexHull::CalculatePositionVectors()
	{
		GMath::MVector res(0.0f);
		GMath::MVector temp(0.0f);

		for (size_t i = 0; i < m_Vertices.size(); i++)
		{
			temp = GMath::LoadVector3(&m_Vertices[i]);
			res = temp - m_Center_Of_Mass;
			m_PositionVectors.emplace_back(res);
		}
	}
}