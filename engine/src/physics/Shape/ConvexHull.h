#pragma once

#include "Shape.h"

namespace PhysicsDEMO
{
	class ConvexHull : public Shape
	{
	public:
		ConvexHull(std::vector<GMath::Vector3> vertices) : m_Vertices(std::move(vertices)) {};
		~ConvexHull() = default;
		virtual MassProperty GetMassProperty(float mass) override;
		virtual GMath::Vector3 GetCenterOfMass() override;
		virtual std::vector<GMath::Vector3> GetPositionVectors() override;
		virtual const std::vector<GMath::Vector3>& GetVertices() const override { return m_Vertices; }

	private:
		std::vector<GMath::Vector3> m_Vertices;
	};
}