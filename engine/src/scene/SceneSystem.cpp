#include "SceneSystem.h"

#include "spdlog/spdlog.h"
#include "physics/Shape/ConvexHull.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace RenderingDEMO
{
	void SceneSystem::Initialize(std::shared_ptr<RenderSystem> render_system, std::shared_ptr<PhysicsDEMO::PhysicsSystem> physics_system)
	{
		m_RenderSystem = render_system;
		m_PhysicsSystem = physics_system;

		std::string bunny_path = "../asset/model/bunny.obj";
		m_BunnyMesh = LoadMesh(bunny_path);
		m_RenderSystem->SubmitMesh(m_BunnyMesh);

		m_BunnyShape = std::make_shared<PhysicsDEMO::ConvexHull>(GetMeshPos(m_BunnyMesh));
		m_BunnyBody = std::make_shared<PhysicsDEMO::Body>();
		m_BunnyBody->SetTranslation(GMath::MVector(1.0f, 1.0f, 0.0f, 0.0f));
		m_BunnyBody->SetRotation(GMath::MQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
	}

	void SceneSystem::OnUpdate(float dt)
	{
		//m_PhysicsSystem->Update(dt);
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
		positions.resize(mesh->Vertices.size());

		for each (const Vertex& vert in mesh->Vertices)
		{
			positions.emplace_back(vert.Position);
		}

		return positions;
	}

	void SceneSystem::LogicToRender()
	{
		PerObjectConstant constant;
		constant.ModelMatrix = m_BunnyBody->GetTransformMatrix();

		m_RenderSystem->SubmitConstant(constant);
	}
}