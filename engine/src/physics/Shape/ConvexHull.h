#pragma once

#include "Shape.h"

namespace PhysicsDEMO
{
	class ConvexHull : public Shape
	{
	public:
		ConvexHull(std::vector<GMath::Vector3> vertices);
		~ConvexHull() = default;
		virtual MassProperty GetMassProperty(float mass) override;
		virtual const GMath::MVector& GetCenterOfMass() override { return m_Center_Of_Mass; }
		virtual const std::vector<GMath::MVector>& GetPositionVectors() override { return m_PositionVectors; }
		virtual const std::vector<GMath::Vector3>& GetVertices() const override { return m_Vertices; }

	private:
		void CalculateCenterOfMass();
		void CalculatePositionVectors();

	private:
		std::vector<GMath::Vector3> m_Vertices;
		std::vector<GMath::MVector> m_PositionVectors;
		GMath::MVector m_Center_Of_Mass;
	};
}