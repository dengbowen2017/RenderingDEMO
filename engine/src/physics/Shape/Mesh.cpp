#include "Mesh.h"

namespace PhysicsDEMO
{
	MassProperty Mesh::GetMassProperty(float mass)
	{
		return MassProperty();
	}

	GMath::Vector3 Mesh::GetCenterOfMass()
	{

		return GMath::Vector3();
	}

	std::vector<GMath::Vector3> Mesh::GetPositionVectors()
	{
		return std::vector<GMath::Vector3>();
	}
}