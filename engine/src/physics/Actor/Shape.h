#pragma once

#include "PhysicMaterial.h"
#include "physics/Geometry/Geometry.h"

namespace PhysicsDEMO
{
	class Shape
	{
	public:
		Shape(std::shared_ptr<Geometry> geometry, std::shared_ptr<PhysicMaterial> material)
			:m_Geometry(geometry), m_Material(material)
		{}

		void SetGeometry(std::shared_ptr<Geometry> geometry) { m_Geometry = geometry; }
		std::shared_ptr<Geometry> GetGeometry() const { return m_Geometry; }
		std::shared_ptr<PhysicMaterial> GetMaterial() const { return m_Material; }

	private:
		std::shared_ptr<PhysicMaterial> m_Material;
		std::shared_ptr<Geometry> m_Geometry;
	};
}