#include "SceneSystem.h"

#include "physics/SimpleFactory.h"
#include "physics/Geometry/ConvexHull.h"
#include "physics/Geometry/Plane.h"

#include "spdlog/spdlog.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace RenderingDEMO
{
	void SceneSystem::Initialize(std::shared_ptr<RenderSystem> render_system, std::shared_ptr<PhysicsDEMO::PhysicsSystem> physics_system)
	{
		m_RenderSystem = render_system;
		m_PhysicsSystem = physics_system;

		m_Camera = std::make_shared<Camera>(GMath::Vector3(1.0f, 2.0f, 3.5f));
		m_RenderSystem->SetSceneCamera(m_Camera);

		std::string bunny_path = "../asset/model/bunny.obj";
		m_BunnyMesh = LoadMesh(bunny_path);
		m_RenderSystem->SubmitMesh(m_BunnyMesh);

		std::shared_ptr<PhysicsDEMO::ConvexHull> bunny_geo = std::make_shared<PhysicsDEMO::ConvexHull>(GetMeshPos(m_BunnyMesh));
		std::shared_ptr<PhysicsDEMO::PhysicMaterial> bunny_mat = std::make_shared<PhysicsDEMO::PhysicMaterial>(0.5f, 0.0f, 0.4f);

		m_BunnyRigidDynamic = PhysicsDEMO::SimpleFactory::CreateRigidDynamic(
			GMath::MVector(1.5f, 2.4f, 0.0f, 0.0f),
			GMath::MQuaternion(0.0f, 0.0f, 0.0f, 1.0f),
			10.0f,
			bunny_geo,
			bunny_mat);

		m_BunnyRigidDynamic->SetLinearDamping(0.99f);
		m_BunnyRigidDynamic->SetAngularDamping(0.98f);
		m_BunnyRigidDynamic->SetLinearVelocity(GMath::MVector(-5.8f, 2.3f, 0.0f, 0.0f));
		m_BunnyRigidDynamic->SetAngularVelocity(GMath::MVector(0.0f, 0.0f, 0.0f, 0.0f));
		m_PhysicsSystem->AddRigidActor(m_BunnyRigidDynamic.get());

		std::shared_ptr<PhysicsDEMO::Plane> planeV_geo = std::make_shared<PhysicsDEMO::Plane>(GMath::MVector(-2.0f, 0.0f, 0.0f, 0.0f), GMath::MQuaternion(0, 0, -GMath::ScalarSin(GMath::ConvertToRadians(45)), GMath::ScalarCos(GMath::ConvertToRadians(45))));
		std::shared_ptr<PhysicsDEMO::PhysicMaterial> planeV_mat = std::make_shared<PhysicsDEMO::PhysicMaterial>();

		m_PlaneVStatic = PhysicsDEMO::SimpleFactory::CreateRigidStatic(
			GMath::MVector(-2.0f, 0.0f, 0.0f, 0.0f),
			GMath::MQuaternion(0, 0, -GMath::ScalarSin(GMath::ConvertToRadians(45)), GMath::ScalarCos(GMath::ConvertToRadians(45))),
			planeV_geo,
			planeV_mat
		);
		m_PhysicsSystem->AddRigidActor(m_PlaneVStatic.get());

		std::shared_ptr<PhysicsDEMO::Plane> planeH_geo = std::make_shared<PhysicsDEMO::Plane>(GMath::MVector(0.0f), GMath::MQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
		std::shared_ptr<PhysicsDEMO::PhysicMaterial> planeH_mat = std::make_shared<PhysicsDEMO::PhysicMaterial>();

		m_PlaneHStatic = PhysicsDEMO::SimpleFactory::CreateRigidStatic(
			GMath::MVector(0.0f),
			GMath::MQuaternion(0.0f, 0.0f, 0.0f, 1.0f),
			planeH_geo,
			planeH_mat
		);
		m_PhysicsSystem->AddRigidActor(m_PlaneHStatic.get());
		
		std::vector<GMath::MVector> velocities(m_BunnyMesh->Vertices.size(), GMath::MVector(-5.8f, 2.3f, 0.0f, 0.0f));
		m_BunnyParticleBuffer = std::make_shared<PhysicsDEMO::ParticleRigidBuffer>(GetMeshPosVec(m_BunnyMesh), velocities, GMath::MVector(1.5f, 2.4f, -2.0f, 0.0f));
		m_PhysicsSystem->AddParticleBuffer(m_BunnyParticleBuffer.get());
	}

	void SceneSystem::OnUpdate(float dt)
	{
		m_PhysicsSystem->Update(dt);
		LogicToRender();
	}

	std::shared_ptr<Mesh> SceneSystem::LoadMesh(const std::string& objPath)
	{
		tinyobj::ObjReaderConfig reader_config;
		tinyobj::ObjReader reader;

		if (!reader.ParseFromFile(objPath, reader_config))
		{
			if (!reader.Error().empty())
			{
				spdlog::error("TinyObjReader: {0}", reader.Error());
			}
			return nullptr;
		}

		if (!reader.Warning().empty())
		{
			spdlog::warn("TinyObjReader: {0}", reader.Warning());
		}

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();

		std::shared_ptr<Mesh> mesh_data = std::make_shared<Mesh>();

		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{
				mesh_data->Indices.push_back(index.vertex_index);
			}
		}

		unsigned int num_verts = attrib.vertices.size() / 3;

		for (size_t i = 0; i < num_verts; i++)
		{
			Vertex vert;

			vert.Position =
			{
				attrib.vertices[i * 3 + 0],
				attrib.vertices[i * 3 + 1],
				attrib.vertices[i * 3 + 2]
			};

			vert.Normal =
			{
				attrib.normals[i * 3 + 0],
				attrib.normals[i * 3 + 1],
				attrib.normals[i * 3 + 2]
			};

			vert.TexCoord = { 0.0f, 0.0f };

			mesh_data->Vertices.push_back(vert);
		}

		return mesh_data;
	}

	std::vector<GMath::Vector3> SceneSystem::GetMeshPos(std::shared_ptr<Mesh> mesh)
	{
		std::vector<GMath::Vector3> positions;
		positions.reserve(mesh->Vertices.size());
		for each (const Vertex& vert in mesh->Vertices)
		{
			positions.emplace_back(vert.Position);
		}
		return positions;
	}

	std::vector<GMath::MVector> SceneSystem::GetMeshPosVec(std::shared_ptr<Mesh> mesh)
	{
		std::vector<GMath::MVector> positions;
		positions.reserve(mesh->Vertices.size());
		for each (const Vertex & vert in mesh->Vertices)
		{
			positions.emplace_back(GMath::LoadVector3(&vert.Position));
		}
		return positions;
	}

	void SceneSystem::LogicToRender()
	{
		// TODO: add ecs to scene system and use scene system to submit transformer to render
		std::vector<PerObjectConstant> constants;

		PerObjectConstant constant;
		constant.ModelMatrix = m_BunnyRigidDynamic->GetModelMatrix();
		constants.push_back(constant);

		constant.ModelMatrix = m_PlaneVStatic->GetModelMatrix();
		constants.push_back(constant);

		constant.ModelMatrix = m_PlaneHStatic->GetModelMatrix();
		constants.push_back(constant);

		constant.ModelMatrix = m_BunnyParticleBuffer->GetModelMatrix();
		constants.push_back(constant);

		m_RenderSystem->SubmitConstants(constants);
	}
}