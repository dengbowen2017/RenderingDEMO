#pragma once

#include "GMath.h"
#include "Geometry.h"

namespace PhysicsDEMO
{
	class ConvexHull : public Geometry
	{
	public:
		ConvexHull(const std::vector<GMath::Vector3>& vertices);
		~ConvexHull() = default;

		const std::vector<GMath::MVector>& GetPositionVectors() const { return m_PositionVectors; }
		const std::vector<GMath::Vector3>& GetVertices() const { return m_Vertices; }
		const GMath::MVector& GetCenterOfMass() { return m_Center_Of_Mass; }
		
		GMath::MMatrix GetInertia(float mass) const;

	private:
		void CalculateCenterOfMass();
		void CalculatePositionVectors();

	private:
		std::vector<GMath::MVector> m_PositionVectors;
		std::vector<GMath::Vector3> m_Vertices;
		GMath::MVector m_Center_Of_Mass;
	};
}