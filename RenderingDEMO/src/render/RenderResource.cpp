#include "RenderResource.h"
#include "RenderUtil.h"

#include <stb_image.h>
#include <spdlog/spdlog.h>

#include <iostream>

namespace RenderingDEMO
{
    void RenderResource::UpdatePerFrameConstant(std::shared_ptr<Camera> camera)
    {
		Eigen::Matrix4f proj = camera->GetProjectionMatrix();
		Eigen::Matrix4f view = camera->GetViewMatrix();

        m_PerFrameConstant.CameraPos = camera->GetCameraPos();
		m_PerFrameConstant.ProjectionViewMatrix = proj * view;

		Eigen::Matrix4f view_no_trans = Eigen::Matrix4f::Zero();
		Eigen::Matrix3f temp = view.block(0, 0, 3, 3);
		view_no_trans.block<3, 3>(0, 0) = temp;

		m_PerFrameConstant.ProjectionViewNoTransMatirx = proj * view_no_trans;
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
		Eigen::Vector3f lightPos(-2.0f, 4.0f, -1.0f);
		Eigen::Matrix4f view = Math::GetLookAtMatrix(lightPos, Eigen::Vector3f::Zero(), Eigen::Vector3f(0.0f, 1.0f, 0.0f));
		Eigen::Matrix4f proj = Math::GetOrthographicMatrix(20, 20, 1.0f, 7.5f);
		Eigen::Matrix4f lightSpaceMat = proj * view;

		DirectionalLight directionallight = { -lightPos, 0.0f, Eigen::Vector3f(1.0f, 1.0f, 1.0f), 0.0f, lightSpaceMat };
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