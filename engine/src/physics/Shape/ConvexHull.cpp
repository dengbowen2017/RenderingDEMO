#include "ConvexHull.h"

namespace PhysicsDEMO
{
	MassProperty ConvexHull::GetMassProperty(float mass)
	{
		MassProperty property;
		property.Mass = mass;
		property.InvMass = 1 / mass;

		std::vector<GMath::Vector3> position_vecs = GetPositionVectors();

		GMath::MMatrix inertia = GMath::MMatrix::Zero();
		GMath::MVector temp;
		for (size_t i = 0; i < position_vecs.size(); i++)
		{
			temp = GMath::LoadVector3(&position_vecs[i]);
			inertia += GMath::PartOfInertiaMatrix(temp);
		}
		property.Inertia = mass * inertia;
		property.InvInertia = GMath::MatrixInverse(property.Inertia);
		return property;
	}

	GMath::Vector3 ConvexHull::GetCenterOfMass()
	{
		GMath::MVector res_temp(0.0f);
		GMath::MVector temp(0.0f);
		for (size_t i = 0; i < m_Vertices.size(); i++)
		{
			temp = GMath::LoadVector3(&m_Vertices[i]);
			res_temp += temp;
		}

		GMath::Vector3 res;
		GMath::StoreVector3(&res, res_temp);
		return res;
	}

	std::vector<GMath::Vector3> ConvexHull::GetPositionVectors()
	{
		std::vector<GMath::Vector3> res_vec;
		res_vec.resize(m_Vertices.size());

		GMath::Vector3 center_temp = GetCenterOfMass();
		GMath::MVector center_of_mass = GMath::LoadVector3(&center_temp);

		GMath::MVector res_temp(0.0f);
		GMath::MVector temp(0.0f);
		GMath::Vector3 res;

		for (size_t i = 0; i < m_Vertices.size(); i++)
		{
			temp = GMath::LoadVector3(&m_Vertices[i]);
			res_temp = temp - center_of_mass;
			GMath::StoreVector3(&res, res_temp);
			res_vec.emplace_back(res);
		}

		return res_vec;
	}
}