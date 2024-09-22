#pragma once

namespace PhysicsDEMO
{
	enum GeometryType
	{
		PLANE,
		CONVEXHULL
	};

	class Geometry
	{
	public:
		virtual ~Geometry() = default;
		GeometryType GetType() const { return m_Type; }

	protected:
		GeometryType m_Type;
	};
}