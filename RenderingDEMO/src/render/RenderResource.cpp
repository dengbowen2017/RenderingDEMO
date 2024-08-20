#include "RenderResource.h"
#include "GMathLib.h"

#include <stb_image.h>
#include <spdlog/spdlog.h>

namespace RenderingDEMO
{
    void RenderResource::UpdatePerFrameConstant(std::shared_ptr<Camera> camera)
    {
		GMath::MMatrix proj = camera->GetProjectionMat();
		GMath::MMatrix view = camera->GetViewMat();

		GMath::Matrix3x3 temp;
		GMath::StoreMatrix3x3(&temp, view);
		GMath::MMatrix view_no_trans = GMath::LoadMatrix3x3(&temp);

		GMath::Matrix4x4 proj_view;
		GMath::StoreMatrix4x4(&proj_view, GMath::MatrixTranspose(proj * view));

		GMath::Matrix4x4 proj_view_no_trans;
		GMath::StoreMatrix4x4(&proj_view_no_trans, GMath::MatrixTranspose(proj * view_no_trans));

        m_PerFrameConstant.CameraPos = camera->GetCameraPos();
		m_PerFrameConstant.ProjectionViewMatrix = proj_view;
		m_PerFrameConstant.ProjectionViewNoTransMatrix = proj_view_no_trans;
    }

    void RenderResource::UpdateBuffers(std::shared_ptr<RHI> rhi)
    {
		float cubeVertices[] =
		{
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		};

		float skyBoxVertices[] =
		{
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,

			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,

			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
		};

		float planeVertices[] =
		{
			 20.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 4.0f, 4.0f,
			 20.0f, -1.0f,  20.0f, 0.0f, 1.0f, 0.0f, 4.0f, 0.0f,
			-20.0f, -1.0f, -20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 4.0f,
			-20.0f, -1.0f,  20.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		};

		unsigned int planeIndices[] =
		{
			0, 3, 1,
			2, 3, 0
		};

		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		unsigned int quadIndices[] =
		{
			0, 1, 2,
			2, 1, 3
		};

		unsigned int stride = 32; // Float3 * 2 + Float2 * 1
		std::shared_ptr<VertexBuffer> vb = rhi->CreateVertexBuffer(cubeVertices, sizeof(cubeVertices), stride);
		m_CubeVertexBuffer = vb;

		vb = rhi->CreateVertexBuffer(planeVertices, sizeof(planeVertices), stride);
		std::shared_ptr<IndexBuffer> ib = rhi->CreateIndexBuffer(planeIndices, sizeof(planeIndices));
		m_PlaneVertexBuffer = vb;
		m_PlaneIndexBuffer = ib;

		stride = 20;
		vb = rhi->CreateVertexBuffer(quadVertices, sizeof(quadVertices), stride);
		ib = rhi->CreateIndexBuffer(quadIndices, sizeof(quadIndices));
		m_QuadVertexBuffer = vb;
		m_QuadIndexBuffer = ib;

		stride = 12;
		vb = rhi->CreateVertexBuffer(skyBoxVertices, sizeof(skyBoxVertices), stride);
		m_SkyBoxVertexBuffer = vb;

		// directional light looking at world zero
		GMath::MVector light_pos = { 3.0f, 4.0f, 2.0f , 0.0f };
		GMath::MVector zero_pos = { 0.0f, 0.0f, 0.0f, 0.0f };
		GMath::MVector world_up = { 0.0f, 1.0f, 0.0f, 0.0f };
		GMath::MMatrix light_view = GMath::MatrixLookAtRH(light_pos, zero_pos, world_up);
		GMath::MMatrix light_proj = GMath::MatrixOrthographicRH(20, 20, 1.0f, 7.5f);

		GMath::Matrix4x4 light_space_mat;
		GMath::StoreMatrix4x4(&light_space_mat, GMath::MatrixTranspose(light_proj* light_view));

		GMath::Vector3 light_pos_neg;
		GMath::StoreVector3(&light_pos_neg, GMath::VectorNegate(light_pos));

		DirectionalLight directionallight = { light_pos_neg, 0.0f, GMath::Vector3(1.0f, 1.0f, 1.0f), 0.0f, light_space_mat };
		m_PerFrameConstant.DirectionalLight = directionallight;

		//PointLight pointlights[] =
		//{
		//	{Eigen::Vector3f(0.0f, 2.0f, 2.0f), 0.09f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.032f}
		//};
		//m_PerFrameConstant.PointLightNum = sizeof(pointlights) / sizeof(PointLight);
		//memcpy(m_PerFrameConstant.PointLights, pointlights, sizeof(pointlights));

		std::shared_ptr<UniformBuffer> ub = rhi->CreateUniformBuffer(sizeof(PerFrameConstant));
		m_PerFrameUniformBuffer = ub;
    }

	std::shared_ptr<Texture2D> RenderResource::LoadTexture(std::shared_ptr<RHI> rhi, std::string texPath)
	{
		std::shared_ptr<Texture2D> texture;
		int width, height, channels;
		// TODO
		// use stbi to identify different types of texutre (16bit, hdr ...)
		// if input channels is 3, we add a alpha channel to be compatible to DirectX
		void* raw_data = stbi_load(texPath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		ResourceRawData texData;
		texData.TextureData.push_back(raw_data);

		if (raw_data)
		{
			unsigned int flags = (unsigned int)TextureFlags::TexShaderResource | (unsigned int)TextureFlags::TexImmutable;
			texture = rhi->CreateTexture2D(width, height, 1, 1, 1, flags, TextureFormat::R8G8B8A8_UNorm, texData);
		}
		else
		{
			spdlog::error("Failed to load texture");
		}
		stbi_image_free(raw_data);
		return texture;
	}

	std::shared_ptr<Texture2D> RenderResource::LoadCubeMap(std::shared_ptr<RHI> rhi, const std::vector<std::string>& cubeMapPaths)
	{
		std::shared_ptr<Texture2D> texture;
		ResourceRawData texDatas;

		int width, height, channels;
		unsigned int flags = (unsigned int)TextureFlags::TexCubeMap | (unsigned int)TextureFlags::TexShaderResource | (unsigned int)TextureFlags::TexImmutable;

		for (size_t i = 0; i < cubeMapPaths.size(); i++)
		{
			void* raw_data = stbi_load(cubeMapPaths[i].c_str(), &width, &height, &channels, STBI_rgb_alpha);
			
			if (raw_data == nullptr)
			{
				spdlog::error("Failed to load {0}", cubeMapPaths[i]);
				return texture;
			}
			texDatas.TextureData.push_back(raw_data);
		}

		texture = rhi->CreateTexture2D(width, height, 6, 1, 1, flags, TextureFormat::R8G8B8A8_UNorm, texDatas);

		for each (void* data in texDatas.TextureData)
		{
			stbi_image_free(data);
		}

		return texture;
	}

	void RenderResource::UploadTextures(std::shared_ptr<RHI> rhi)
	{
		std::string wall_texture_path = "../asset/texture/wall.jpg";
		std::string box_texture_path = "../asset/texture/box.png";

		std::vector<std::string> cubemap_paths = {
			"../asset/texture/Cubemap_right.png",
			"../asset/texture/Cubemap_left.png",
			"../asset/texture/Cubemap_up.png",
			"../asset/texture/Cubemap_down.png",
			"../asset/texture/Cubemap_back.png",
			"../asset/texture/Cubemap_front.png",
		};

		m_BoxTexture = LoadTexture(rhi, box_texture_path);
		m_WallTexture = LoadTexture(rhi, wall_texture_path);
		m_SkyBoxTexture = LoadCubeMap(rhi, cubemap_paths);
	}
}