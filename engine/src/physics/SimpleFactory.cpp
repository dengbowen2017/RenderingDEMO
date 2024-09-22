#include "SimpleFactory.h"

#include "physics/Geometry/ConvexHull.h"
#include "physics/Geometry/Plane.h"

namespace PhysicsDEMO
{
	std::shared_ptr<RigidDynamic> SimpleFactory::CreateRigidDynamic(const GMath::MVector& position, const GMath::MQuaternion& rotation, float mass, std::shared_ptr<Geometry> geo, std::shared_ptr<PhysicMaterial> material)
	{
		std::shared_ptr<RigidDynamic> rigid_dynamic = std::make_shared<RigidDynamic>(position, rotation);
		std::shared_ptr<Shape> rigid_shape = std::make_shared<Shape>(geo, material);

		rigid_dynamic->AttachShape(rigid_shape);

		switch (geo->GetType())
		{
		case GeometryType::CONVEXHULL:
			ConvexHull* convex_hull = (ConvexHull*)(geo.get());
			rigid_dynamic->SetMassAndInertia(mass, convex_hull->GetInertia(mass));
		}

		return rigid_dynamic;
	}

	std::shared_ptr<RigidStatic> SimpleFactory::CreateRigidStatic(const GMath::MVector& position, const GMath::MQuaternion& rotation, std::shared_ptr<Geometry> geo, std::shared_ptr<PhysicMaterial> material)
	{
		std::shared_ptr<RigidStatic> rigid_static = std::make_shared<RigidStatic>(position, rotation);
		std::shared_ptr<Shape> rigid_shape = std::make_shared<Shape>(geo, material);

		rigid_static->AttachShape(rigid_shape);

		return rigid_static;
	}
}