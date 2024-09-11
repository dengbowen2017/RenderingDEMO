#include "ConvexHull.h"

namespace PhysicsDEMO
{
	ConvexHull::ConvexHull(std::vector<GMath::Vector3> vertices)
		:m_Vertices(std::move(vertices))
	{
		CalculateCenterOfMass();
		CalculatePositionVectors();
	}

	MassProperty ConvexHull::GetMassProperty(float mass)
	{
		MassProperty property;
		property.Mass = mass;
		property.InvMass = 1 / mass;

		std::vector<GMath::MVector> position_vecs = GetPositionVectors();

		GMath::MMatrix inertia = GMath::MMatrix::Zero();

		for (size_t i = 0; i < position_vecs.size(); i++)
		{
			inertia += GMath::PartOfInertiaMatrix(position_vecs[i]);
		}

		inertia *= mass / position_vecs.size();
		inertia.r[3] = GMath::g_MatIdentityR3;

		property.Inertia = inertia;
		property.InvInertia = GMath::MatrixInverse(property.Inertia);
		return property;
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

		m_Center_Of_Mass = res;
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