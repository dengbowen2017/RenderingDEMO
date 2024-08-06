#pragma once

#include "RHI.h"
#include "RHIResource.h"
#include "RenderDefinition.h"
#include "Camera.h"

namespace RenderingDEMO
{
	class RenderResource
	{
	public:
		void UpdatePerFrameConstant(std::shared_ptr<Camera> camera);
		
		// temp
		void UpdateBuffers(std::shared_ptr<RHI> rhi);
		void UploadTextures(std::shared_ptr<RHI> rhi);

	private:
		std::shared_ptr<Texture2D> LoadTexture(std::shared_ptr<RHI> rhi, std::string texPath);
		std::shared_ptr<Texture2D> LoadCubeMap(std::shared_ptr<RHI> rhi, const std::vector<std::string>& cubeMapPaths);

	public:
		// temp 
		// need Mesh and Object class to manage all the buffers
		std::shared_ptr<VertexBuffer> m_CubeVertexBuffer;
		std::shared_ptr<VertexBuffer> m_SkyBoxVertexBuffer;

		std::shared_ptr<VertexBuffer> m_PlaneVertexBuffer;
		std::shared_ptr<IndexBuffer> m_PlaneIndexBuffer;

		std::shared_ptr<VertexBuffer> m_QuadVertexBuffer;
		std::shared_ptr<IndexBuffer> m_QuadIndexBuffer;

		std::shared_ptr<UniformBuffer> m_PerFrameUniformBuffer;

		std::shared_ptr<Texture2D> m_WallTexture;
		std::shared_ptr<Texture2D> m_BoxTexture;
		std::shared_ptr<Texture2D> m_SkyBoxTexture;

		PerFrameConstant m_PerFrameConstant;
	};
}