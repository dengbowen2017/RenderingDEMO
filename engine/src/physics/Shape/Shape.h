#pragma once

#include "GMath.h"
#include "physics/Body/MassProperty.h"
 
namespace PhysicsDEMO
{
	class Shape
	{
	public:
		virtual ~Shape() = default;
		virtual MassProperty GetMassProperty(float mass) = 0;
		virtual const GMath::MVector& GetCenterOfMass() = 0;
		virtual const std::vector<GMath::MVector>& GetPositionVectors() = 0;
		virtual const std::vector<GMath::Vector3>& GetVertices() const = 0;
	};
}