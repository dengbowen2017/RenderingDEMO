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
		virtual GMath::Vector3 GetCenterOfMass() = 0;
		virtual std::vector<GMath::Vector3> GetPositionVectors() = 0;
		virtual const std::vector<GMath::Vector3>& GetVertices() const = 0;
	};
}