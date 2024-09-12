#include "CollisionSolver.h"

#include "physics/Body/Body.h"

namespace PhysicsDEMO
{
	void CollisionSolver::ImpulseSolver(const Collision& collision)
	{
		GMath::MVector v_n = GMath::VectorDot(collision.Plane.Normal, collision.Velocity) * collision.Plane.Normal;
		GMath::MVector v_t = collision.Velocity - v_n;

		Body* body = collision.ActiveBody;
		float a = 1 - body->m_PhysicMaterial.Friction * (1 + body->m_PhysicMaterial.Restitution) * GMath::VectorGetX(GMath::VectorMagnitude(v_n)) / GMath::VectorGetX(GMath::VectorMagnitude(v_t));
		a = a > 0.0 ? a : 0.0f;

		v_n *= -body->m_PhysicMaterial.Restitution;
		v_t *= a;

		GMath::MVector now_center_of_mass = body->m_Shape->GetCenterOfMass() + body->m_Translation;
		GMath::MMatrix R = GMath::QuaternionToMatrix(body->m_Rotation);
		GMath::MMatrix cross_mat = GMath::VectorCrossToMatrix(collision.Point - now_center_of_mass);
		GMath::MMatrix K = body->m_MassProperty.InvMass * GMath::MMatrix::Identity() - cross_mat * R * body->m_MassProperty.InvInertia * GMath::MatrixTranspose(R) * cross_mat;
		K.r[3] = GMath::g_MatIdentityR3;

		GMath::MMatrix K_inv = GMath::MatrixInverse(K);
		GMath::MVector vec = v_t + v_n - collision.Velocity;

		GMath::MVector impulse = K_inv * vec;
		GMath::MVector torque = cross_mat * impulse;

		body->ApplyImpluse(impulse);
		body->ApplyTorque(torque);
	}
}


