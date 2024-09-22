#pragma once

#include "render/RenderSystem.h"
#include "render/Camera.h"

#include "physics/PhysicsSystem.h"
#include "physics/Actor/RigidDynamic.h"
#include "physics/Actor/RigidStatic.h"

#include "DataDefinition.h"

namespace RenderingDEMO
{
	class SceneSystem
	{
	public:
		~SceneSystem() = default;

		void Initialize(std::shared_ptr<RenderSystem> render_system, std::shared_ptr<PhysicsDEMO::PhysicsSystem> physics_system);
		void OnUpdate(float dt);

		std::shared_ptr<Camera> GetSceneCamera() const { return m_Camera; }

	private:
		std::shared_ptr<Mesh> LoadMesh(const std::string& objPath);
		std::vector<GMath::Vector3> GetMeshPos(std::shared_ptr<Mesh> mesh);

		void LogicToRender();

	private:
		std::shared_ptr<RenderSystem> m_RenderSystem;
		std::shared_ptr<PhysicsDEMO::PhysicsSystem> m_PhysicsSystem;

		// Render
		std::shared_ptr<Camera> m_Camera;

		// Mesh
		std::shared_ptr<Mesh> m_BunnyMesh;

		// Physics
		std::shared_ptr<PhysicsDEMO::RigidDynamic> m_BunnyRigidDynamic;
		std::shared_ptr<PhysicsDEMO::RigidStatic> m_PlaneVStatic;
		std::shared_ptr<PhysicsDEMO::RigidStatic> m_PlaneHStatic;
	};
}