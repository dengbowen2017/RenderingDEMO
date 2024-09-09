#pragma once

#include "render/RenderSystem.h"
#include "physics/PhysicsSystem.h"

#include "DataDefinition.h"

namespace RenderingDEMO
{
	class SceneSystem
	{
	public:
		~SceneSystem() = default;

		void Initialize(std::shared_ptr<RenderSystem> render_system, std::shared_ptr<PhysicsDEMO::PhysicsSystem> physics_system);
		void OnUpdate(float dt);

	private:
		std::shared_ptr<Mesh> LoadMesh(const std::string& objPath);
		std::vector<GMath::Vector3> GetMeshPos(std::shared_ptr<Mesh> mesh);

		void LogicToRender();

	private:
		std::shared_ptr<RenderSystem> m_RenderSystem;
		std::shared_ptr<PhysicsDEMO::PhysicsSystem> m_PhysicsSystem;

		std::shared_ptr<Mesh> m_BunnyMesh;

		std::shared_ptr<PhysicsDEMO::Body> m_BunnyBody;
		std::shared_ptr<PhysicsDEMO::Shape> m_BunnyShape;
	};
}