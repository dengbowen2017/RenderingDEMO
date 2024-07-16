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
		void UpdateBuffers(std::shared_ptr<RHI> rhi);

	public:
		// temp 
		// need Mesh and Object class to manage all the buffers
		std::shared_ptr<VertexBuffer> m_CubeVertexBuffer;

		std::shared_ptr<VertexBuffer> m_PlaneVertexBuffer;
		std::shared_ptr<IndexBuffer> m_PlaneIndexBuffer;

		std::shared_ptr<VertexBuffer> m_QuadVertexBuffer;
		std::shared_ptr<IndexBuffer> m_QuadIndexBuffer;

		std::shared_ptr<UniformBuffer> m_PerFrameUniformBuffer;

		PerFrameConstant m_PerFrameConstant;
	};
}